/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:51:51 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/19 11:31:15 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_error.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_md5.h"
#include "ft_ssl_dbg.h"
#include <time.h>

#define TEST_SIZE 100000 * 10000

static clock_t	g_begin;
static int		g_timetrial;

/*
** Functions  ******************************************************************
*/

static t_ft_ssl_status	get_timetest_input(t_hash_input *input)
{
	t_ft_ssl_status ret;
	uint8_t			*random;
	size_t			tmp;
	double			load;

	random = (uint8_t *)ft_memalloc(TEST_SIZE);
	ret = FT_SSL_OK;
	ret = open_file("/dev/urandom", &input->fd, O_RDONLY);
	while (input->input_length + 64 <= TEST_SIZE)
	{
		tmp = TEST_SIZE - input->input_length;
		ret = read_file(input->fd, random + input->input_length, &tmp);
		if (ret != FT_SSL_OK && ret != FT_SSL_WANT_READ)
		{
			free(random);
			return (ret);
		}
		input->input_length += tmp;
		load = ((double)input->input_length / (double)(TEST_SIZE)) * 100;
		ft_printf("Loading %.2f%%\r", load);
	}
	ret = close_file(input->fd);
	if (ret != FT_SSL_OK)
		free(random);
	input->fd = -1;
	input->input = random;
	ft_printf("Time trial. Digesting %.2llu bytes\n", input->input_length);
	g_begin = clock();
	g_timetrial = 1;
	return (ret);
}

static void		print_timetest_results(size_t processed_bytes)
{
	clock_t		end;
	double		elapsed;
	double		bps;

	end = clock();
	elapsed = (double)(end - g_begin) / CLOCKS_PER_SEC;
	bps = (double)processed_bytes / elapsed;
	ft_printf("Time = %.6f seconds\nSpeed = %.6f bytes/second\n", elapsed, bps);
}

static t_ft_ssl_status	get_input(int argc, char **argv, t_hash_input *input)
{
	t_ft_ssl_status	ret;

	ret = FT_SSL_OK;
	ft_bzero(input, sizeof(t_hash_input));
	input->fd = -1;
	if (argc > 1 && ft_strequ(argv[0], "-s"))
	{
		input->input = (uint8_t *)argv[1];
		input->input_length =ft_strlen(argv[1]);
	}
	else if (argc)
		if (ft_strequ(argv[0], "-t"))
			ret = get_timetest_input(input);
		else
			ret = open_file(argv[0], &input->fd, O_RDONLY);
	else
		ret = FT_SSL_INVALID_ARGUMENT;
	return (ret);
}

static t_hashfnc	get_hash_function(char *name)
{
	if (ft_strequ(name, "md5"))
		return (md5_main);
	return (NULL);
}

int		hash_main(int argc, char **argv)
{
	char			*out;
	t_hash_input	input;
	t_hashfnc		fnc;
	t_ft_ssl_status	ret;

	g_timetrial = 0;
	if (argc)
	{
		fnc = get_hash_function(argv[0]);
		if (!fnc)
			return (FT_SSL_UNDEFINED);
		ret = get_input(argc - 1, argv + 1, &input);
		if (ret != FT_SSL_OK)
			return (ret);
		out = NULL;
		out = fnc(&input);
		ft_printf("%s\n", out);
		free(out);
		if (input.fd > 2)
			ret = close_file(input.fd);
		if (g_timetrial)
			print_timetest_results(input.input_length);
		return (ret);
	}
	ft_printf("\nNot implemented!\n");
	ft_printf("%u\n", sizeof(t_md5_state));
	return (FT_SSL_UNDEFINED);
}
