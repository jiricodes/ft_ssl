/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:03:05 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 11:18:41 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_UTILS_H
# define FT_SSL_UTILS_H

/*
** Includes ********************************************************************
*/

# include <unistd.h>
# include <inttypes.h>

/*
** Defines *********************************************************************
*/

# define HEXSTRING	"0123456789abcdef"

/*
** Function Prototypes *********************************************************
*/

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *buffer, size_t len, int fd);
size_t	ft_strlen(char *buffer);

#endif
