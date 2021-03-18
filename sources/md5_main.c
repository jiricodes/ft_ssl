/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:45:46 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/18 13:04:21 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_error.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_md5.h"
#include "ft_ssl_dbg.h"

/*
** Functions  ******************************************************************
*/

static int				md5_pad(uint8_t *buffer, ssize_t buffer_len,
								t_md5_block *block)
{
	static int64_t	total_len;
	int ret;
	static int padded;

	ret = 1;
	ft_bzero(block, MD5_BLOCK_SIZE);
	if (DEBUG)
		ft_printf("%llu | pad %d\n", buffer_len, padded);
	if (buffer_len >= MD5_BLOCK_SIZE)
	{
		ft_memcpy(block, buffer, MD5_BLOCK_SIZE);
		total_len += MD5_BLOCK_SIZE;
	}
	else
	{
		if (buffer_len > 0 && !padded)
		{
			ft_memcpy(block, buffer, buffer_len);
			block->xp[buffer_len] = 0b10000000;
			total_len += buffer_len;
		}
		else if (!padded)
			block->xp[0] = 0b10000000;
		padded = 1;
		if (buffer_len < MD5_PAD_REM)
		{
			total_len *= 8;
			ft_memcpy(&block->x[14], &total_len, 8);
			if (DEBUG)
				ft_printf("Total len = %llu\n", total_len);
			total_len = 0;
			ret = 0;
			padded = 0;
		}
	}
	if (DEBUG)
		ft_printf("ret = %d | pad %d\n", ret, padded);
	return (ret);
}

static void				md5_init(t_md5_state *state)
{
	state->bufs.four[0] = 0x67452301;
	state->bufs.four[1] = 0xefcdab89;
	state->bufs.four[2] = 0x98badcfe;
	state->bufs.four[3] = 0x10325476;
}

static t_ft_ssl_status	md5_loop_str(
	uint8_t *input,
	ssize_t input_length,
	t_md5_state *state)
{
	ssize_t			i;
	t_ft_ssl_status	err;
	int				run;

	i = 0;
	run = 1;
	if (DEBUG)
		ft_printf("Input: %s\nLength: %lu\n", input, input_length);
	while (run)
	{
		run = md5_pad(input + i, input_length - i, &state->block);
		if (DEBUG)
		{
			err = uint8_print_fmt((uint8_t *)&state->block, MD5_BLOCK_SIZE);
			if (err != FT_SSL_OK)
				return (err);
		}
		err = md5_block(state);
		if (err != FT_SSL_OK)
			return (err);
		i += MD5_BLOCK_SIZE;
	}
	return (FT_SSL_OK);
}

static t_ft_ssl_status	md5_loop_file(
	int fd,
	t_md5_state *state)
{
	t_ft_ssl_status	err;
	int				run;
	uint8_t			input[MD5_BLOCK_SIZE];
	ssize_t			input_length;

	run = 1;
	while (run)
	{
		input_length = MD5_BLOCK_SIZE;
		ft_bzero(input, MD5_BLOCK_SIZE);
		err = read_file(fd, (uint8_t *)input, &input_length);
		if (err != FT_SSL_EOF && err != FT_SSL_WANT_READ)
			return (err);
		run = md5_pad(input, input_length, &state->block);
		if (DEBUG)
		{
			err = uint8_print_fmt((uint8_t *)&state->block, MD5_BLOCK_SIZE);
			if (err != FT_SSL_OK)
				return (err);
		}
		err = md5_block(state);
		if (err != FT_SSL_OK);
	}
	return (FT_SSL_OK);
}

char					*md5_main(t_hash_input *input)
{
	t_md5_state		state;
	size_t			i;
	t_ft_ssl_status	err;
	char			*out;
	size_t			out_size;

	err = FT_SSL_OK;
	out = NULL;
	out_size = 0;
	md5_init(&state);
	if (input->fd == -1)
		err = md5_loop_str(input->input, input->input_length, &state);
	else
		err = md5_loop_file(input->fd, &state);
	if (err == FT_SSL_OK)
	{
		if ((err = ft_to_hexstr((uint8_t *)&state.bufs, \
				MD5_OUT_SIZE, &out, &out_size)) != FT_SSL_OK)
			out = NULL;
	}
	return (out);
}
