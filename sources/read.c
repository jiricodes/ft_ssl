/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:55:10 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/17 21:10:16 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_utils.h"

#define BUFF 64

/*
** Functions  ******************************************************************
*/

t_ft_ssl_status	open_file(const char *filename, int *fd, int flag)
{
	int		ret;

	ret = open(filename, O_RDONLY, 0);
	if (ret == -1)
		return (FT_SSL_OPEN_FAIL);
	*fd = ret;
	return (FT_SSL_OK);
}

t_ft_ssl_status	close_file(int *fd)
{
	int		ret;

	ret = close(fd);
	if (ret == -1)
		return (FT_SSL_CLOSE_FAIL);
	*fd = ret;
	return (FT_SSL_OK);
}

t_ft_ssl_status	read_file(int fd, uint8_t **out, size_t *out_size)
{
	ssize_t		ret;

	
	ret = read(fd, *out, *out_size);
	if (ret == -1)
		return (FT_SSL_READ_FAIL);
	else if (ret == 0)
		return (FT_SSL_EOF);
	else
	
	//read and return N * MD_BLOCK
	// Return FT_SSL_WANT_READ if not eof?
	// then main loop can process and fetch more as needed
	// use out_size as input for buf size?
}