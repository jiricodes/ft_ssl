/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:51:51 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/16 20:24:36 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_error.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_md5.h"

/*
** Functions  ******************************************************************
*/

int 	pad_test(uint8_t *buffer, size_t buffer_len, t_md5_block *block)
{
	static int64_t total_len;
	int				i;
	
	ft_bzero(block, MD5_BLOCK_SIZE);
	if (buffer_len >= MD5_BLOCK_SIZE)
	{
		ft_memcpy(block, buffer, MD5_BLOCK_SIZE);
		total_len += MD5_BLOCK_SIZE;
		return (MD5_BLOCK_SIZE);
	}
	else if (buffer_len > MD5_PAD_REM)
	{
		ft_memcpy(block, buffer, buffer_len);
		block->xp[buffer_len] = 0b10000000;
		total_len += MD5_BLOCK_SIZE;
		return (buffer_len);
	}
	else
	{
		ft_memcpy(block, buffer, buffer_len);
		block->xp[buffer_len] = 0b10000000;
		total_len += buffer_len;
		total_len *= 8;
		i = 0;
		while (i < 9)
		{
			block->xp[MD5_BLOCK_SIZE - 1 - i] = (uint8_t)(total_len >> (i * 8));
			i++;
		}
		// ft_memcpy(&block->xp[MD5_PAD_REM], &total_len, sizeof(int64_t));
		ft_printf("Total len = %llu\n", total_len);
		return (buffer_len);
	}
	// should have different value (maybe error even tho it shouldn't happen)
	return (INT32_MAX);
}

int		md5_init(t_md5_state *state)
{
		state->bufs.four[0] = 0x67452301;
		state->bufs.four[1] = 0xefcdab89;
		state->bufs.four[2] = 0x98badcfe;
		state->bufs.four[3] = 0x10325476;
	return (FT_SSL_OK);
}

int		hash_main(int argc, char **argv)
{
	t_md5_block	block;
	t_md5_state	state;
	char		*out;
	size_t		out_size;
	int			ret;
	int			tmp;
	int			err;

	md5_init(&state);
	uint8_t	test[5] = {0b01100001, 0b01100010, 0b01100011, 0b01100100, 0b01100101};
	if (argc > 1)
	{
		ft_bzero(&block, sizeof(t_md5_block));
		ssize_t len = strlen(argv[1]);
		ret = 0;
		ft_printf("Input: %s\nLength: %lu\n", argv[1], len);
		while (ret < len)
		{
			tmp = pad_test(argv[1] + ret, len - ret, &state.block);
			out = NULL;
			out_size = 0;
			if ((err = ft_to_hexstr((uint8_t *)&state.block, MD5_BLOCK_SIZE, &out, &out_size)) != FT_SSL_OK)
				return (err);
			ft_print_fmt_block(out);
			free(out);
			err = md5_block(&state);
			ret += tmp;
		}
		out = NULL;
		out_size = 0;
		if ((err = ft_to_hexstr((uint8_t *)&state.bufs, MD5_OUT_SIZE, &out, &out_size)) != FT_SSL_OK)
			return (err);
		ft_printf("Result: ");
		ft_print_fmt_block(out);
		free(out);
		return (0);
	}
	ft_printf("\nNot implemented!\n");
	ft_printf("%u\n", sizeof(t_md5_state));
}
