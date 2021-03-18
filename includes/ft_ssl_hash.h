/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_hash.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:56:58 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/18 12:37:33 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HASH_H
# define FT_SSL_HASH_H

/*
** Includes ********************************************************************
*/

# include <inttypes.h>
# include <string.h>	

typedef struct		s_ft_ssl_hash_input
{
	uint8_t		*input;
	size_t		input_length;
	int			fd;
}					t_hash_input;

typedef char*		(*t_hashfnc)(t_hash_input*);

int		hash_main(int argc, char **argv);

#endif
