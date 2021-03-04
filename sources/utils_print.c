/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:52:28 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 16:23:50 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_utils.h"

/*
** Functions *******************************************************************
*/

int		ft_print_binary_fd(uint8_t *bytestream, size_t len, int fd)
{
	char	*bitstr;
	size_t	bitlen;
	int		ret;

	if ((ret = ft_to_binstr(bytestream, len, &bitstr, &bitlen)) != FT_SSL_OK)
		return (ret);
	if ((ret = ft_putstr_fd(bitstr, fd)) != (int)bitlen)
	{
		free(bitstr);
		return (FT_SSL_WRITE_FAIL);
	}
	free(bitstr);
	return (FT_SSL_OK);
}

int		ft_print_hex_fd(uint8_t *bytestream, size_t len, int fd)
{
	char	*hexstr;
	size_t	hexlen;
	int		ret;

	if ((ret = ft_to_hexstr(bytestream, len, &hexstr, &hexlen)) != FT_SSL_OK)
		return (ret);
	if ((ret = ft_putstr_fd(hexstr, fd)) != hexlen)
	{
		free(hexstr);
		return (FT_SSL_WRITE_FAIL);
	}
	free(hexstr);
	return (FT_SSL_OK);
}
