/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:56:20 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 12:10:47 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include <assert.h>
#include <string.h>
#include "ft_ssl_utils.h"

/*
** Functions *******************************************************************
*/

static void	unittest_binstr()
{
	int n;
	int ret;
	char *out;
	size_t out_len;

	n = 0;
	ret = ft_to_binstr((uint8_t *)&n, 4, &out, &out_len);
	assert(ret == 0);
	assert(!strcmp(out, "00000000 00000000 00000000 00000000"));
	free(out);
	n = 1;
	ret = ft_to_binstr((uint8_t *)&n, 4, &out, &out_len);
	assert(ret == 0);
	assert(!strcmp(out, "00000000 00000000 00000000 00000001"));
	free(out);
	n = -1;
	ret = ft_to_binstr((uint8_t *)&n, 4, &out, &out_len);
	assert(ret == 0);
	assert(!strcmp(out, "11111111 11111111 11111111 11111111"));
	free(out);
	n = 42;
	ret = ft_to_binstr((uint8_t *)&n, 4, &out, &out_len);
	assert(ret == 0);
	assert(!strcmp(out, "00000000 00000000 00000000 00101010"));
	free(out);
	n = 42694269;
	ret = ft_to_binstr((uint8_t *)&n, 4, &out, &out_len);
	assert(ret == 0);
	assert(!strcmp(out, "00000010 10001011 01110110 01111101"));
	free(out);
}

int			main(void)
{

}
