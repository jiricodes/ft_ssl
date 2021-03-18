/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:09:45 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/18 12:39:00 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

/*
** Includes ********************************************************************
*/

# include <inttypes.h>
# include <string.h>
# include "ft_ssl_error.h"
# include "ft_ssl_utils.h"
# include "ft_ssl_hash.h"
# include "libft.h"

/*
** Defines *********************************************************************
*/

# define MD5_BLOCK_SIZE 64
# define MD5_PAD_REM 56
# define MD5_OUT_SIZE 16

/*
** Data Structures *************************************************************
*/

typedef uint32_t	(*t_ft_round)(uint32_t, uint32_t, uint32_t);

typedef union		u_md5_buffers
{
	uint8_t		one[16];
	uint32_t	four[4];
}					t_md5_buffers;

typedef union		u_md5_block
{
	uint8_t		xp[MD5_BLOCK_SIZE];
	uint32_t	x[MD5_BLOCK_SIZE / 4];
}					t_md5_block;

typedef struct		s_ft_ssl_md5_state
{
	t_md5_buffers	bufs;
	t_md5_block		block;
}					t_md5_state;

typedef struct		s_ft_ssl_md5_operation
{
	uint8_t		o[4];
	uint8_t		ix;
	uint8_t		s;
	uint32_t	t;
	t_ft_round	fnc;
}					t_md5_op;

/*
** Function Prototypes *********************************************************
*/

uint32_t			ft_md5_f(uint32_t b, uint32_t c, uint32_t d);
uint32_t			ft_md5_g(uint32_t b, uint32_t c, uint32_t d);
uint32_t			ft_md5_h(uint32_t b, uint32_t c, uint32_t d);
uint32_t			ft_md5_i(uint32_t b, uint32_t c, uint32_t d);
int					md5_block(t_md5_state *state);
char				*md5_main(t_hash_input *input);

#endif
