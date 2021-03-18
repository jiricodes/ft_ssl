/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:51:51 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/18 12:44:55 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_error.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_md5.h"
#include "ft_ssl_dbg.h"

/*
** Functions  ******************************************************************
*/
static t_ft_ssl_status	get_input(int argc, char **argv, t_hash_input *input)
{
	ft_bzero(input, sizeof(t_hash_input));
	input->fd = -1;
}

static t_ft_ssl_status	get_hash_function(char *name, t_hashfnc	*fnc)
{
	if (ft_strequ(name, "md5"))
	{
		fnc = &md5_main;
		return (FT_SSL_OK);
	}
	return (FT_SSL_INVALID_COMMAND);
}

int		hash_main(int argc, char **argv)
{
	char			*out;
	t_hash_input	input;
	t_hashfnc		fnc;
	t_ft_ssl_status	ret;

	if (argc)
	{
		ret = get_hash_function(argv[0], &fnc);
		if (ret != FT_SSL_OK)
			return (ret);
		ret = get_input(argc - 1, argv + 1, &input);
		if (ret != FT_SSL_OK)
			return (ret);
		out = NULL;
		if (ft_strequ(argv[0], "md5"))
		{
			if (argc > 2 && ft_strequ(argv[1], "-s"))
				out = md5_main(argv[2], ft_strlen(argv[1]));
		}
		ft_printf("%s\n", out);
		free(out);
		return (0);
	}
	ft_printf("\nNot implemented!\n");
	ft_printf("%u\n", sizeof(t_md5_state));
}
