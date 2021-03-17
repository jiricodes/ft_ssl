# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/03 12:11:21 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/17 12:34:56 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl_test
CC ?= gcc

INCLUDES = -I ../includes/ -I ../libft/includes

CFLAGS = 

ifdef VERB
CFLAGS += -DVERBOSE=1
endif

LDFLAGS = -L ../libft -lft

SRC_FILES =	error.c \
			hash.c \
			md5_functions.c \
			md5_main.c \
			md5_round.c \
			utils_bits.c \
			utils_print.c \
			utils_string.c

SOURCES_DIR = ../sources

SOURCES = $(addprefix $(SOURCES_DIR)/, $(SRC_FILES))

GEN_MD5_PREFIX = test_md5_

GEN_SRCS =	$(GEN_MD5_PREFIX)f.c \
			$(GEN_MD5_PREFIX)g.c \
			$(GEN_MD5_PREFIX)h.c \
			$(GEN_MD5_PREFIX)i.c
			

GEN_N ?= 1000

TEST_SRCS = $(GEN_SRCS) \
			test.c

SOURCES += $(TEST_SRCS)

TEST_FILES =	result \
				simple \
				tmp_leftshiftgen

OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean fclean re

all: build run

gen-files:
	./scripts/create_list_md5funcs.sh $(GEN_N) $(GEN_MD5_PREFIX)
	@sleep 1

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

build:
	make gen-files
	make -C ../libft
	make $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LDFLAGS)

run:
	./$(NAME)

clean:
	-@rm $(OBJECTS) 2> /dev/null || true
	-@rm $(GEN_SRCS) 2> /dev/null || true
	-@rm $(TEST_FILES) 2> /dev/null || true
	-@rm files/$(TEST_FILES) 2> /dev/null || true
	-@rm scripts/$(TEST_FILES) 2> /dev/null || true

fclean: clean
	-@rm $(NAME) 2> /dev/null || true

re: fclean all

print:
	@echo "$(SOURCES)"
	@echo "$(OBJECTS)"