# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/03 12:11:21 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/03 21:23:55 by jnovotny         ###   ########.fr        #
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
			md5_functions.c \
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

.PHONY: all $(NAME) clean fclean re

all: $(NAME) run

gen-files:
	./scripts/create_list_md5funcs.sh $(GEN_N) $(GEN_MD5_PREFIX)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): gen-files $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)

run:
	./$(NAME)

clean:
	-rm $(OBJECTS)
	-rm $(GEN_SRCS)
	-rm $(TEST_FILES)
	-rm files/$(TEST_FILES)
	-rm scripts/$(TEST_FILES)

fclean: clean
	-rm $(NAME)

re: fclean all