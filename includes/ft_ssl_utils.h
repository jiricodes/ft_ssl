/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:03:05 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/17 20:57:06 by jnovotny         ###   ########.fr       */
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
# include "libft.h"

/*
** Defines *********************************************************************
*/

# define HEXSTRING	"0123456789abcdef"

/*
** Function Prototypes *********************************************************
*/

int				ft_to_binstr(
					uint8_t *bytestream,
					size_t len,
					char **out,
					size_t *out_len);
int				ft_to_hexstr(
					uint8_t *bytestream,
					size_t len,
					char **out,
					size_t *out_len);
uint32_t		ft_uint32_left_circular_shift(uint32_t	input, size_t shift);
void			ft_print_fmt_block(const char *buf);
t_ft_ssl_status	uint8_print_fmt(uint8_t *buffer, size_t buffer_size);
t_ft_ssl_status	ft_print_binary_fd(uint8_t *bytestream, size_t len, int fd);
t_ft_ssl_status	ft_print_hex_fd(uint8_t *bytestream, size_t len, int fd);
#endif
