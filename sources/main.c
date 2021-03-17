/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:21:15 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/17 12:19:39 by jnovotny         ###   ########.fr       */
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
			ft_printf("%s\n", g_cmdlist[i].name);
		i++;
	}
}

void			usage(void)
{
	ft_printf(USAGE);
	ft_printf(STD_CMD_STR);
	print_cmds(CMD_STD);
	ft_printf(HASH_CMD_STR);
	print_cmds(CMD_HASH);
	ft_printf(CIPH_CMD_STR);
	print_cmds(CMD_CIPH);
}

static int		console(void)
{
	ft_printf("Console mode not implemented!\n");
	return (0);
}

int				main(int argc, char **argv)
{
	int		i;

	if (argc < 2)
		return (console());
	i = 0;
	while (g_cmdlist[i].name && argv[1])
	{
		if (ft_strequ(g_cmdlist[i].name, argv[1]))
			return (g_cmdlist[i].cmd_fnc(argc - 1, argv + 1));
		i++;
	}
	error_exit(FT_SSL_INVALID_COMMAND, argv[1], &usage);
	return (0);
}
