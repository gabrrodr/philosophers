# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 13:37:47 by gabrrodr          #+#    #+#              #
#    Updated: 2023/10/19 15:22:26 by gabrrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -g -Wall -Wextra -Werror -g3 -fsanitize=thread -O3 -march=native
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRC = 	main.c \
		init.c \
		free.c \
		utils.c \
		routines.c \
	  	actions.c \
		logs.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all