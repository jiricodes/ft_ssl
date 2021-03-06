/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:25:32 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 18:37:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_utils.h"

/*
** Functions *******************************************************************
*/

/*
** @brief	Converts input stream of bytes into string of bits values.
**			Bytes are separated by " " character. Output memory is
**			alocated if needed.
**
** @param	bytestream	Input stream of bytes
** @param	len			Number of bytes to process
** @param	out			Output string pointer
** @param	out_len		Output string length
**
** @return	int			FT_SSL_OK or error indicator
*/

int		ft_to_binstr(
			uint8_t *bytestream,
			size_t len,
			char **out,
			size_t *out_len)
{
	int		i;
	char	c;
	size_t	x;
	char	*buf;

	*out_len = len * 9 - 1;
	if (*out == NULL)
	{
		if ((buf = (char *)malloc(*out_len + 1)) == NULL)
			return (FT_SSL_MALLOC_FAIL);
		buf[*out_len] = '\0';
	}
	else
		buf = *out;
	x = 0;
	while (len > 0)
	{
		i = 8;
		while (i-- > 0)
			buf[x++] = ((bytestream[len - 1] >> i) & 1) + 48;
		if (len-- > 1)
			buf[x++] = ' ';
	}
	*out = buf;
	return (FT_SSL_OK);
}

int		ft_to_hexstr(
			uint8_t *bytestream,
			size_t len,
			char **out,
			size_t *out_len)
{
	int					i;
	size_t				x;
	char				*buf;
	static const char	hex[] = HEXSTRING;

	*out_len = len * 2;
	if (*out == NULL)
	{
		if ((buf = (char *)malloc(*out_len + 1)) == NULL)
			return (FT_SSL_MALLOC_FAIL);
		buf[*out_len] = '\0';
	}
	else
		buf = *out;
	i = 0;
	while (i < len)
	{
		x = bytestream[i] / 16;
		buf[i * 2] = hex[x];
		x = bytestream[i] % 16;
		buf[i * 2 + 1] = hex[x];
		i++;
	}
	*out = buf;
	return (FT_SSL_OK);
}
