/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:03:05 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 10:00:15 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_UTILS_H
# define FT_SSL_UTILS_H

/*
** Includes ********************************************************************
*/

# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>
# include "ft_ssl_error.h"

/*
** Defines *********************************************************************
*/

# define HEXSTRING	"0123456789abcdef"

/*
** Function Prototypes *********************************************************
*/

int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *buffer, size_t len, int fd);
size_t		ft_strlen(char *buffer);
int			ft_to_binstr(
				uint8_t *bytestream,
				size_t len,
				char **out,
				size_t *out_len);
int			ft_to_hexstr(
				uint8_t *bytestream,
				size_t len,
				char **out,
				size_t *out_len);
uint32_t	ft_uint32_left_circular_shift(uint32_t	input, size_t shift);
#endif
