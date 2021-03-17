/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_round.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:34:44 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/17 12:19:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_md5.h"
#include <assert.h>
#include "ft_ssl_dbg.h"

/*
** Variables  ******************************************************************
*/

/*
** Consider using only starting index 'r' then (r + [0, 1, 2, 3])%4
**
** Static variables for every round as set in rfc1321. The constant T[i]
** could be calculated with per 'i' (2^32 * abs(sin(i)); where i is in radians),
** however since they are always the same it's performance beneficial
** to define them statically. Especially when we would have defined X[k] and
** s per round anyways.
*/
static const t_md5_op	g_op[64] = {
	{{0, 1, 2, 3}, 0, 7, 0xd76aa478, ft_md5_f},
	{{3, 0, 1, 2}, 1, 12, 0xe8c7b756, ft_md5_f},
	{{2, 3, 0, 1}, 2, 17, 0x242070db, ft_md5_f},
	{{1, 2, 3, 0}, 3, 22, 0xc1bdceee, ft_md5_f},
	{{0, 1, 2, 3}, 4, 7, 0xf57c0faf, ft_md5_f},
	{{3, 0, 1, 2}, 5, 12, 0x4787c62a, ft_md5_f},
	{{2, 3, 0, 1}, 6, 17, 0xa8304613, ft_md5_f},
	{{1, 2, 3, 0}, 7, 22, 0xfd469501, ft_md5_f},
	{{0, 1, 2, 3}, 8, 7, 0x698098d8, ft_md5_f},
	{{3, 0, 1, 2}, 9, 12, 0x8b44f7af, ft_md5_f},
	{{2, 3, 0, 1}, 10, 17, 0xffff5bb1, ft_md5_f},
	{{1, 2, 3, 0}, 11, 22, 0x895cd7be, ft_md5_f},
	{{0, 1, 2, 3}, 12, 7, 0x6b901122, ft_md5_f},
	{{3, 0, 1, 2}, 13, 12, 0xfd987193, ft_md5_f},
	{{2, 3, 0, 1}, 14, 17, 0xa679438e, ft_md5_f},
	{{1, 2, 3, 0}, 15, 22, 0x49b40821, ft_md5_f},
	{{0, 1, 2, 3}, 1, 5, 0xf61e2562, ft_md5_g},
	{{3, 0, 1, 2}, 6, 9, 0xc040b340, ft_md5_g},
	{{2, 3, 0, 1}, 11, 14, 0x265e5a51, ft_md5_g},
	{{1, 2, 3, 0}, 0, 20, 0xe9b6c7aa, ft_md5_g},
	{{0, 1, 2, 3}, 5, 5, 0xd62f105d, ft_md5_g},
	{{3, 0, 1, 2}, 10, 9, 0x2441453, ft_md5_g},
	{{2, 3, 0, 1}, 15, 14, 0xd8a1e681, ft_md5_g},
	{{1, 2, 3, 0}, 4, 20, 0xe7d3fbc8, ft_md5_g},
	{{0, 1, 2, 3}, 9, 5, 0x21e1cde6, ft_md5_g},
	{{3, 0, 1, 2}, 14, 9, 0xc33707d6, ft_md5_g},
	{{2, 3, 0, 1}, 3, 14, 0xf4d50d87, ft_md5_g},
	{{1, 2, 3, 0}, 8, 20, 0x455a14ed, ft_md5_g},
	{{0, 1, 2, 3}, 13, 5, 0xa9e3e905, ft_md5_g},
	{{3, 0, 1, 2}, 2, 9, 0xfcefa3f8, ft_md5_g},
	{{2, 3, 0, 1}, 7, 14, 0x676f02d9, ft_md5_g},
	{{1, 2, 3, 0}, 12, 20, 0x8d2a4c8a, ft_md5_g},
	{{0, 1, 2, 3}, 5, 4, 0xfffa3942, ft_md5_h},
	{{3, 0, 1, 2}, 8, 11, 0x8771f681, ft_md5_h},
	{{2, 3, 0, 1}, 11, 16, 0x6d9d6122, ft_md5_h},
	{{1, 2, 3, 0}, 14, 23, 0xfde5380c, ft_md5_h},
	{{0, 1, 2, 3}, 1, 4, 0xa4beea44, ft_md5_h},
	{{3, 0, 1, 2}, 4, 11, 0x4bdecfa9, ft_md5_h},
	{{2, 3, 0, 1}, 7, 16, 0xf6bb4b60, ft_md5_h},
	{{1, 2, 3, 0}, 10, 23, 0xbebfbc70, ft_md5_h},
	{{0, 1, 2, 3}, 13, 4, 0x289b7ec6, ft_md5_h},
	{{3, 0, 1, 2}, 0, 11, 0xeaa127fa, ft_md5_h},
	{{2, 3, 0, 1}, 3, 16, 0xd4ef3085, ft_md5_h},
	{{1, 2, 3, 0}, 6, 23, 0x4881d05, ft_md5_h},
	{{0, 1, 2, 3}, 9, 4, 0xd9d4d039, ft_md5_h},
	{{3, 0, 1, 2}, 12, 11, 0xe6db99e5, ft_md5_h},
	{{2, 3, 0, 1}, 15, 16, 0x1fa27cf8, ft_md5_h},
	{{1, 2, 3, 0}, 2, 23, 0xc4ac5665, ft_md5_h},
	{{0, 1, 2, 3}, 0, 6, 0xf4292244, ft_md5_i},
	{{3, 0, 1, 2}, 7, 10, 0x432aff97, ft_md5_i},
	{{2, 3, 0, 1}, 14, 15, 0xab9423a7, ft_md5_i},
	{{1, 2, 3, 0}, 5, 21, 0xfc93a039, ft_md5_i},
	{{0, 1, 2, 3}, 12, 6, 0x655b59c3, ft_md5_i},
	{{3, 0, 1, 2}, 3, 10, 0x8f0ccc92, ft_md5_i},
	{{2, 3, 0, 1}, 10, 15, 0xffeff47d, ft_md5_i},
	{{1, 2, 3, 0}, 1, 21, 0x85845dd1, ft_md5_i},
	{{0, 1, 2, 3}, 8, 6, 0x6fa87e4f, ft_md5_i},
	{{3, 0, 1, 2}, 15, 10, 0xfe2ce6e0, ft_md5_i},
	{{2, 3, 0, 1}, 6, 15, 0xa3014314, ft_md5_i},
	{{1, 2, 3, 0}, 13, 21, 0x4e0811a1, ft_md5_i},
	{{0, 1, 2, 3}, 4, 6, 0xf7537e82, ft_md5_i},
	{{3, 0, 1, 2}, 11, 10, 0xbd3af235, ft_md5_i},
	{{2, 3, 0, 1}, 2, 15, 0x2ad7d2bb, ft_md5_i},
	{{1, 2, 3, 0}, 9, 21, 0xeb86d391, ft_md5_i}
};

/*
** Functions  ******************************************************************
*/

static void		md5_do_op(
	t_md5_buffers *bufs,
	t_md5_block *block,
	const t_md5_op *op)
{
	uint32_t	tmp;

	bufs->four[op->o[0]] += op->fnc(bufs->four[op->o[1]],
									bufs->four[op->o[2]],
									bufs->four[op->o[3]]) +
							block->x[op->ix] +
							op->t;
	bufs->four[op->o[0]] = ft_uint32_left_circular_shift(\
								bufs->four[op->o[0]], \
								op->s);
	bufs->four[op->o[0]] += bufs->four[op->o[1]];
}

int				md5_block(t_md5_state *state)
{
	t_md5_buffers	buffers;
	uint8_t			i;

	buffers.four[0] = state->bufs.four[0];
	buffers.four[1] = state->bufs.four[1];
	buffers.four[2] = state->bufs.four[2];
	buffers.four[3] = state->bufs.four[3];
	i = 0;
	while (i < 64)
	{
		md5_do_op(&buffers, &state->block, &g_op[i]);
		if (LOG)
		{
			ft_printf("%02u: A=%u, B=%u, C=%u, D=%u\n",
				i, buffers.four[0], buffers.four[1],
				buffers.four[2], buffers.four[3]);
		}
		i++;
	}
	state->bufs.four[0] += buffers.four[0];
	state->bufs.four[1] += buffers.four[1];
	state->bufs.four[2] += buffers.four[2];
	state->bufs.four[3] += buffers.four[3];
	return (FT_SSL_OK);
}
