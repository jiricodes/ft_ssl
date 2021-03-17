/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:51:51 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/17 12:16:04 by jnovotny         ###   ########.fr       */
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

int		hash_main(int argc, char **argv)
{
	char		*out;

	if (argc > 1)
	{
		out = NULL;
		if (ft_strequ(argv[0], "md5"))
		{
			out = md5_main(argv[1], ft_strlen(argv[1]));
		}
		ft_printf("Result: ");
		ft_print_fmt_block(out);
		free(out);
		return (0);
	}
	ft_printf("\nNot implemented!\n");
	ft_printf("%u\n", sizeof(t_md5_state));
}
