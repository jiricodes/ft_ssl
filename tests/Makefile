# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/03 12:11:21 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/03 12:18:22 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl_test
CC ?= gcc

INCLUDES = -I ../includes/

CFLAGS = 

SOURCES =	test.c \
			error.c \
			utils_print.c \
			utils_string.c

SOURCES_DIR = ../sources

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME):
	@echo "Compiling $(NAME)"

run:
	./$(NAME)

clean:
	@echo "clean"

fclean: clean
	@echo "fclean"

re: fclean all