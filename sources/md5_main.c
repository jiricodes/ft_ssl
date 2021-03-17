/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:45:46 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/17 11:46:46 by jnovotny         ###   ########.fr       */
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

void 	md5_pad(uint8_t *buffer, size_t buffer_len, t_md5_block *block)
{
	static int64_t	total_len;
	
	ft_bzero(block, MD5_BLOCK_SIZE);
	if (buffer_len >= MD5_BLOCK_SIZE)
	{
		ft_memcpy(block, buffer, MD5_BLOCK_SIZE);
		total_len += MD5_BLOCK_SIZE;
	}
	else if (buffer_len > MD5_PAD_REM)
	{
		ft_memcpy(block, buffer, buffer_len);
		block->xp[buffer_len] = 0b10000000;
		total_len += buffer_len;
	}
	else
	{
		ft_memcpy(block, buffer, buffer_len);
		block->xp[buffer_len] = 0b10000000;
		total_len += buffer_len;
		total_len *= 8;
		ft_memcpy(&block->x[14], &total_len, 8);
		ft_printf("Total len = %llu\n", total_len);
	}
}

void	md5_init(t_md5_state *state)
{
		state->bufs.four[0] = 0x67452301;
		state->bufs.four[1] = 0xefcdab89;
		state->bufs.four[2] = 0x98badcfe;
		state->bufs.four[3] = 0x10325476;
}

char	*md5_main(uint8_t *input, size_t input_length)
{
	t_md5_state		state;
	size_t			i;
	t_ft_ssl_error	err;
	char			*out;
	size_t			out_size;

	err = FT_SSL_OK;
	md5_init(&state);
	i = 0;
	ft_printf("Input: %s\nLength: %lu\n", input, input_length);
	while (i <= input_length)
	{
		md5_pad(input + i, input_length - i, &state.block);
		if (DEBUG)
		{
			err = print_fmt((uint8_t *)&state.block, MD5_BLOCK_SIZE);
			if (err != FT_SSL_OK)
				return (NULL); 
		}
		err = md5_block(&state);
		if (err != FT_SSL_OK)
				return (NULL);
		i += MD5_BLOCK_SIZE;
	}
	out = NULL;
	out_size = 0;
	if ((err = ft_to_hexstr((uint8_t *)&state.bufs, MD5_OUT_SIZE, &out, &out_size)) != FT_SSL_OK)
		return (NULL);
	return (out);
}
