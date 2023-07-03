# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 18:01:38 by ljerinec          #+#    #+#              #
#    Updated: 2023/07/03 13:39:52 by ljerinec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Werror -Wextra
CC = gcc

SRCS = 	sources/philo.c \
		sources/checking.c \
		sources/parsing.c \
		sources/threads.c \
		sources/utils.c \
		sources/actions.c \

PRINT_NAME		= philo
PRINT_PREFIX	= \033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

OBJECTS = $(SRCS:%.c=%.o)
OBJECTSBONUS = $(SRCSBONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m\n"
	$(CC) $(CFLAGS) -o philo $(OBJECTS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

clean:
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@rm -f $(OBJECTS) $(OBJECTSBONUS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f philo_bonus

re: fclean all

.PHONY: all clean fclean re bonus