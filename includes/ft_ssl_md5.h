/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:09:45 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 20:18:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

/*
** Includes ********************************************************************
*/

# include <inttypes.h>

/*
** Function Prototypes *********************************************************
*/

uint32_t	ft_md5_f(uint32_t b, uint32_t c, uint32_t d);
uint32_t	ft_md5_g(uint32_t b, uint32_t c, uint32_t d);
uint32_t	ft_md5_h(uint32_t b, uint32_t c, uint32_t d);
uint32_t	ft_md5_i(uint32_t b, uint32_t c, uint32_t d);

#endif
