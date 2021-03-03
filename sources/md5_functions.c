/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:09:26 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 20:17:44 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

uint32_t	ft_md5_f(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (~b & d));
}

uint32_t	ft_md5_g(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & d) | (c & ~d));
}

uint32_t	ft_md5_h(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

uint32_t	ft_md5_i(uint32_t b, uint32_t c, uint32_t d)
{
	return (c ^ (b | ~d));
}
