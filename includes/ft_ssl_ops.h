/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_ops.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:41:44 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 13:24:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_OPS_H
# define FT_SSL_OPS_H

typedef int			(*t_cmd_fnc)(int argc, char **argv);

enum				e_cmd_type
{
	CMD_NONE,
	CMD_STD,
	CMD_HASH,
	CMD_CIPH
};

typedef struct		s_cmd_dict
{
	const char		*name;
	enum e_cmd_type	cmd_type;
	t_cmd_fnc		cmd_fnc;
}					t_cmds;

#endif