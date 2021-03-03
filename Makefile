# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 16:00:45 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/03 12:25:50 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC ?= gcc

INCLUDES = -I includes/

CFLAGS = 

LDFLAGS = 

SRC_FILES =	error.c \
			main.c \
			utils_print.c \
			utils_string.c

SOURCES_DIR = sources
SOURCES = $(addprefix $(SOURCES_DIR)/, $(SRC_FILES))

OBJECTS = $(SOURCES:.c=.o)

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)

test:
	make -C tests

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(NAME)

re: fclean all