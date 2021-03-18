/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:26:39 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/18 11:48:16 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_error.h"
#include "ft_ssl_utils.h"
#include "stddef.h"

static t_ft_ssl_status_info	g_error_info[] = {
	{
		FT_SSL_OK,
		"OK",
		NULL
	},
	{
		FT_SSL_UNDEFINED,
		"Undefined Error",
		NULL
	},
	{
		FT_SSL_WRITE_FAIL,
		"System call write was not successful",
		"Try to check errno for additional information"
	},
	{
		FT_SSL_READ_FAIL,
		"System call read was not successful",
		"Try to check errno for additional information"
	},
	{
		FT_SSL_WANT_READ,
		"There's more data on the file descriptor to be read",
		NULL
	},
	{
		FT_SSL_EOF,
		"Function reached EOF",
		NULL
	},
	{
		FT_SSL_SMALL_BUFFER,
		"Provided buffer is too small",
		"Check documentation for minimum buffer size"
	},
	{
		FT_SSL_OPEN_FAIL,
		"System call open was not successful",
		"Try to check errno for additional information"
	},
	{
		FT_SSL_CLOSE_FAIL,
		"System call close was not successful",
		"Try to check errno for additional information"
	},
	{
		FT_SSL_MALLOC_FAIL,
		"System call malloc was not successful",
		"Try to check errno for additional information"
	},
	{
		FT_SSL_INVALID_COMMAND,
		" is an invalid command.",
		"Check the list of available commands."
	},
	{
		FT_SSL_INVALID_ARGUMENT,
		" is an invalid argument.",
		NULL
	},
	{
		FT_SSL_INVALID_ERROR,
		"Invalid error number invoked",
		NULL
	},
};

void	error_exit(t_ft_ssl_status e, char *arg, void (*f)(void))
{
	int		i;

	i = 0;
	while (g_error_info[i].error_id != FT_SSL_INVALID_ERROR && \
			g_error_info[i].error_id != e)
		i++;
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(g_error_info[i].error_message, \
				STDERR_FILENO);
	if (f)
		f();
	exit(g_error_info[i].error_id);
}
