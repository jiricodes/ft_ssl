# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 16:00:45 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/17 12:22:56 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC ?= gcc

INC_DIR = includes

INCLUDES = -I $(INC_DIR)/ -I libft/includes

CFLAGS = 

LDFLAGS = -L libft -lft

LIBFT = libft/libft.a

SRC_FILES =	error.c \
			hash.c \
			main.c \
			md5_functions.c \
			md5_main.c \
			md5_round.c \
			utils_bits.c \
			utils_print.c \
			utils_string.c

SOURCES_DIR = sources
SOURCES = $(addprefix $(SOURCES_DIR)/, $(SRC_FILES))

OBJECTS = $(SOURCES:.c=.o)

NORM_CMD ?= ~/.norminette/norminette.rb

LIBFT_DIRS =	libft/includes \
				libft/sources/error_srcs \
				libft/sources/libft_srcs \
				libft/sources/pf_srcs

C_BLUE=\033[34m
C_EOC=\033[0m


.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LDFLAGS)

test: norm-silent check-forbidden-silent
	@make -C tests

test-verb: norm check-forbidden
	@echo "$(C_BLUE)Running UNITTEST$(C_EOC)"
	@make -C tests VERB=1

norm:
	@echo "$(C_BLUE)Norminette check$(C_EOC)"
	@./tests/scripts/check_norm.sh $(NORM_CMD) $(SOURCES_DIR) $(INC_DIR) $(LIBFT_DIRS)
	@echo ""

norm-silent:
	@make norm > /dev/null

check-forbidden:
	@echo "$(C_BLUE)Forbidden functions check$(C_EOC)"
	@./tests/scripts/check_forbidden.sh tests/files/forbidden_list $(SOURCES_DIR) $(INC_DIR) $(LIBFT_DIRS)
	@echo ""

check-forbidden-silent:
	@make check-forbidden > /dev/null

GIT_COMMENT ?= "autosave"
git-autosave:
	@git add .
	@git commit -m $(GIT_COMMENT)
	git push

clean:
	-@make clean -C tests || true
	-@make clean -C libft || true
	-@rm $(OBJECTS) 2> /dev/null || true

fclean: clean
	-@make fclean -C tests || true
	-@make fclean -C libft || true
	-@rm $(NAME) 2> /dev/null || true

re: fclean all