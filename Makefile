# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 16:00:45 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/04 09:50:51 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC ?= gcc

INC_DIR = includes

INCLUDES = -I $(INC_DIR)/

CFLAGS = 

LDFLAGS = 

SRC_FILES =	error.c \
			main.c \
			utils_bits.c \
			utils_print.c \
			utils_string.c

SOURCES_DIR = sources
SOURCES = $(addprefix $(SOURCES_DIR)/, $(SRC_FILES))

OBJECTS = $(SOURCES:.c=.o)

NORM_CMD ?= ~/.norminette/norminette.rb

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)

test:
	make -C tests

test-verb: norm check-forbidden
	make -C tests VERB=1

norm:
	@./tests/scripts/check_norm.sh $(NORM_CMD) $(SOURCES_DIR) $(INC_DIR)

check-forbidden:
	@./tests/scripts/check_forbidden.sh $(SOURCES_DIR) $(INC_DIR)

clean:
	-rm $(OBJECTS)

fclean: clean
	-rm $(NAME)

re: fclean all