# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 16:00:45 by jnovotny          #+#    #+#              #
#    Updated: 2021/03/02 16:59:28 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

INCLUDES = -I includes/

SOURCES =	main.c \
			error.c


.PHONY: all $(NAME) clean fclean re

all: $(NAME)

$(name):
	@echo "Compiling $(NAME)"

clean:
	@echo "clean"

fclean: clean
	@echo "fclean"

re: fclean all