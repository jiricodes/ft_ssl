/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:26:39 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 10:58:55 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_error.h"
#include "stddef.h"

static t_ft_ssl_error_info	g_error_info[] = {
	{
		FT_SSL_OK,
		"OK",
		NULL
	},

};
