/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:51:51 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/18 12:53:15 by jnovotny         ###   ########.fr       */
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
	t_ft_ssl_status	ret;

	ret = FT_SSL_OK;
	ft_bzero(input, sizeof(t_hash_input));
	input->fd = -1;
	if (argc > 1 && ft_strequ(argv[0], "-s"))
	{
		input->input = argv[1];
		input->input_length =ft_strlen(argv[1]);
	}
	else if (argc)
		ret = open_file(argv[0], &input->fd, O_RDONLY);
	else
		ret = FT_SSL_INVALID_ARGUMENT;
	return (ret);
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
		out = fnc(&input);
		ft_printf("%s\n", out);
		free(out);
		return (FT_SSL_OK);
	}
	ft_printf("\nNot implemented!\n");
	ft_printf("%u\n", sizeof(t_md5_state));
	return (FT_SSL_UNDEFINED);
}
