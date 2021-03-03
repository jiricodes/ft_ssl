# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/03 12:11:21 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/03 20:02:40 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl_test
CC ?= gcc

INCLUDES = -I ../includes/

CFLAGS = 

ifdef VERB
CFLAGS += -DVERBOSE=1
endif

LDFLAGS = 

SRC_FILES =	error.c \
			utils_bits.c \
			utils_print.c \
			utils_string.c

SOURCES_DIR = ../sources

SOURCES = $(addprefix $(SOURCES_DIR)/, $(SRC_FILES))

SOURCES += test.c

OBJECTS = $(SOURCES:.c=.o)

.PHONY: all $(NAME) clean fclean re

all: $(NAME) run

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)

run:
	./$(NAME)

clean:
	-rm $(OBJECTS)

fclean: clean
	-rm $(NAME)

re: fclean all