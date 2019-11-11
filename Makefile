#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plettie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 19:40:06 by plettie           #+#    #+#              #
#    Updated: 2019/11/09 19:40:08 by plettie          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC := gcc

NAME := minishell

FLAGS := -Wall -Wextra -Werror

SOURCE := Sources/check.c Sources/do_something.c Sources/env.c Sources/ft.c Sources/ft_strsplit.c Sources/list.c Sources/minishell.c

OBJECTS := $(SOURCE:.c=.o)

GREEN= \033[1;32m
RED= \033[1;31m

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)Project is successfully compiled"

$(OBJECTS): %.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJECTS)
	@echo "$(RED)Deleting objects files"

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(OBJECTS)
	@echo "$(RED)Deleting projects files"

re : fclean all

