/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:02:33 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/03 21:30:11 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_TEST_H
# define FT_SSL_TEST_H

/*
** Includes ********************************************************************
*/

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "ft_ssl_utils.h"
#include "ft_ssl_md5.h"

/*
** DEFINES **********************************************************************
*/

#ifndef VERBOSE
# define VERBOSE 0
#endif

/*
** Macros **********************************************************************
*/

#define CATEGORY(s)		if (VERBOSE) printf("\nTEST: %s\n", s)
#define STATUS(c, t)	if (VERBOSE) printf("%s%4d / %4d [%3.0f%%]\n", \
								c != 1 ? "\033[1A\r" : "", \
								c, t, ((float)c/(float)t) * 100)

/*
** Function Prototypes *********************************************************
*/

void unittest_md5f();
void unittest_md5g();
void unittest_md5h();
void unittest_md5i();
#endif