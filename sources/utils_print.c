/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:52:28 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/17 20:57:06 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_utils.h"

/*
** Functions *******************************************************************
*/

t_ft_ssl_status		ft_print_binary_fd(uint8_t *bytestream, size_t len, int fd)
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

t_ft_ssl_status		ft_print_hex_fd(uint8_t *bytestream, size_t len, int fd)
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

void				ft_print_fmt_block(const char *buf)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(buf);
	i = 0;
	while (i < len)
	{
		ft_printf("%.8s", &buf[i]);
		i += 8;
		if (i >= len || i % 32 == 0)
			ft_printf("\n");
		else
			ft_printf(" ");
	}
}

t_ft_ssl_status		uint8_print_fmt(uint8_t *buffer, size_t buffer_size)
{
	char			*out;
	size_t			out_size;
	t_ft_ssl_status	err;

	err = FT_SSL_OK;
	out = NULL;
	out_size = 0;
	err = ft_to_hexstr(buffer, buffer_size, &out, &out_size);
	if (err == FT_SSL_OK)
	{
		ft_print_fmt_block(out);
		free(out);
	}
	return (err);
}
