/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:51:51 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/15 15:33:37 by jnovotny         ###   ########.fr       */
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
	//allocate
	//set values for init and current (one by one faster than memcpy)
	// word A: 0x67452301
    // word B: 0xefcdab89
    // word C: 0x98badcfe
    // word D: 0x10325476
	// fnc = f
	//
	state = (t_md5_state *)ft_memalloc(sizeof(t_md5_state));
	if (!state)
		return (FT_SSL_MALLOC_FAIL);
	state->init.four[0] = 0x67452301;
	state->init.four[1] = 0xefcdab89;
	state->init.four[2] = 0x98badcfe;
	state->init.four[3] = 0x10325476;
	state->current.four[0] = 0x67452301;
	state->current.four[1] = 0xefcdab89;
	state->current.four[2] = 0x98badcfe;
	state->current.four[3] = 0x10325476;
	state->fnc = ft_md5_f;
	state->buf = NULL;
	state->buf_size = 0;
	ft_bzero(&state->props, sizeof(t_md5_props));
	return (FT_SSL_OK);
}

int		hash_main(int argc, char **argv)
{
	t_md5_block	block;
	char		*out;
	size_t		out_size;
	int			ret;
	int			tmp;
	int			err;

	uint8_t	test[5] = {0b01100001, 0b01100010, 0b01100011, 0b01100100, 0b01100101};
	if (argc > 1)
	{
		ft_bzero(&block, sizeof(t_md5_block));
		ssize_t len = 5;
		ret = 0;
		while (ret < len)
		{
			tmp = pad_test(test + ret, len - ret, &block);
			out = NULL;
			out_size = 0;
			if ((err = ft_to_hexstr((uint8_t *)&block, MD5_BLOCK_SIZE, &out, &out_size)) != FT_SSL_OK)
				return (err);
			for (int x =0; x < 16; x++)
			{
				ft_printf("%ld\n", block.x[x]);
			}
			ret += tmp;
			ft_print_fmt_block(out);
		}
		
		return (0);
	}
	ft_printf("\nNot implemented!\n");
	

	ft_printf("%u %u %u %u %u | %u\n", \
		sizeof(t_md5_block), \
		sizeof(ft_round), \
		sizeof(uint8_t*), \
		sizeof(size_t), \
		sizeof(t_md5_props), \
		sizeof(t_md5_state));
}
