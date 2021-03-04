/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:46:57 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 16:19:06 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putendl_fd(char const *s, int fd)
{
	int ret;

	ret = 0;
	if (s)
	{
		ret = write(fd, s, ft_strlen(s));
		if (ret < 0)
			return (ret);
		ret += write(fd, "\n", 1);
	}
	return (ret);
}
