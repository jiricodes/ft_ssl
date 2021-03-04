/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:47:22 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/04 14:19:04 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_ERROR_H
# define FT_SSL_ERROR_H

typedef enum		e_ft_ssl_error
{
	FT_SSL_OK,
	FT_SSL_UNDEFINED,
	FT_SSL_WRITE_FAIL,
	FT_SSL_MALLOC_FAIL,
	FT_SSL_INVALID_COMMAND,
	FT_SSL_INVALID_ARGUMENT,
	FT_SSL_INVALID_ERROR = 0xFF
}					t_ft_ssl_error;

typedef struct		s_ft_ssl_error
{
	t_ft_ssl_error	error_id;
	char			*error_message;
	char			*additional_information;
}					t_ft_ssl_error_info;

void				error_exit(t_ft_ssl_error e, char *arg, void (*f)(void));

#endif
