/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:52:28 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 11:55:17 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_utils.h"

/*
** Functions *******************************************************************
*/

int		ft_putchar_fd(char c, int fd)
{
	int ret;

	ret = write(fd, &c, 1);
	if (ret != 1)
		return (FT_SSL_WRITE_FAIL);
	return (FT_SSL_OK);
}

int		ft_putstr_fd(char *buffer, size_t len, int fd)
{
	int ret;

	ret = write(fd, buffer, len);
	if (ret != len)
		return (FT_SSL_WRITE_FAIL);
	return (FT_SSL_OK);
}

size_t	ft_strlen(char *buffer)
{
	size_t len;

	len = 0;
	while (*buffer != 0)
	{
		len++;
		buffer++;
	}
	return (len);
}

int		ft_print_binary_fd(uint8_t	*bytestream, size_t len, int fd)
{
	char	*bitstr;
	size_t	bitlen;
	int		ret;

	if ((ret = ft_to_binstr(bytestream, len, &bitstr, &bitlen)) != FT_SSL_OK)
		return (ret);
	if ((ret = ft_putstr_fd(bitstr, bitlen, fd)) != FT_SSL_OK)
	{
		free(bitstr);
		return (ret);
	}
	free(bitstr);
	return (FT_SSL_OK);
}
