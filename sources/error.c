/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:26:39 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 14:12:32 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_error.h"
#include "ft_ssl_utils.h"
#include "stddef.h"

static t_ft_ssl_error_info	g_error_info[] = {
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

void	error_exit(t_ft_ssl_error e, char *arg, void (*f)(void))
{
	int		i;

	i = 0;
	while (g_error_info[i].error_id != FT_SSL_INVALID_ERROR && \
			g_error_info[i].error_id != e)
		i++;
	ft_putstr_fd("Error: ", 7, STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, ft_strlen(arg), STDERR_FILENO);
	ft_putstr_fd(g_error_info[i].error_message, \
				ft_strlen(g_error_info[i].error_message), \
				STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (f)
		f();
	exit(g_error_info[i].error_id);
}
