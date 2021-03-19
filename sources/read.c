/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:55:10 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/19 11:33:05 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_utils.h"

#define READ_BUF_SIZE 10000

/*
** Functions  ******************************************************************
*/

t_ft_ssl_status	open_file(const char *filename, int *fd, int flag)
{
	int		ret;

	ret = open(filename, flag, 0);
	if (ret == -1)
		return (FT_SSL_OPEN_FAIL);
	*fd = ret;
	return (FT_SSL_OK);
}

t_ft_ssl_status	close_file(int fd)
{
	int		ret;

	ret = close(fd);
	if (ret == -1)
		return (FT_SSL_CLOSE_FAIL);
	return (FT_SSL_OK);
}

t_ft_ssl_status	read_file(int fd, uint8_t *out, size_t *out_size)
{
	ssize_t		ret;
	uint8_t		buf[READ_BUF_SIZE];

	// if (*out_size < READ_BUF_SIZE)
	// 	return (FT_SSL_SMALL_BUFFER);
	ret = read(fd, (uint8_t *)buf, READ_BUF_SIZE < *out_size ? READ_BUF_SIZE : *out_size);
	if (ret == -1)
		return (FT_SSL_READ_FAIL);
	else if (ret == 0)
	{
		*out_size = 0;
		return (FT_SSL_EOF);
	}
	else
	{
		ft_memcpy(out, buf, ret);
		*out_size = ret;
		return (FT_SSL_WANT_READ);
	}
}
