/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:56:13 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 09:50:16 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_utils.h"

uint32_t	ft_uint32_left_circular_shift(uint32_t input, size_t shift)
{
	uint32_t out;

	out = (input << shift) | (input >> (sizeof(input) * 8 - shift));
	return (out);
}
