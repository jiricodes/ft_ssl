/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:21:15 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 14:13:13 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_ops.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_hash.h"

/*
** Defines *********************************************************************
*/

#define USAGE "usage: ft_ssl command [command opts] [command args]\n"
#define STD_CMD_STR "\nStandard commands:\n"
#define HASH_CMD_STR "\nMessage Digest commands:\n"
#define CIPH_CMD_STR "\nCipher commands:\n"

/*
** Variables *******************************************************************
*/

static const t_cmds		g_cmdlist[] = {
	{"md5", CMD_HASH, hash_main},
	{"sha256", CMD_HASH, hash_main},
	{NULL, CMD_NONE, NULL}
};

/*
** Functions  ******************************************************************
*/
static void		print_cmds(enum e_cmd_type t)
{
	int i;

	i = 0;
	while (g_cmdlist[i].name)
	{
		if (t == g_cmdlist[i].cmd_type)
		{
			ft_putstr_fd(g_cmdlist[i].name, \
						ft_strlen(g_cmdlist[i].name), \
						STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
}

void			usage()
{
	ft_putstr_fd(USAGE, ft_strlen(USAGE), STDOUT_FILENO);
	ft_putstr_fd(STD_CMD_STR, ft_strlen(STD_CMD_STR), STDOUT_FILENO);
	print_cmds(CMD_STD);
	ft_putstr_fd(HASH_CMD_STR, ft_strlen(HASH_CMD_STR), STDOUT_FILENO);
	print_cmds(CMD_HASH);
	ft_putstr_fd(CIPH_CMD_STR, ft_strlen(CIPH_CMD_STR), STDOUT_FILENO);
	print_cmds(CMD_CIPH);
}

int				main(int argc, char **argv)
{
	if (argc < 2)
	{
		usage();
		return (FT_SSL_INVALID_COMMAND);
	}
	error_exit(FT_SSL_INVALID_COMMAND, "foo", &usage);
	return (0);
}
