# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 17:53:16 by khanhayf          #+#    #+#              #
#    Updated: 2023/03/05 15:53:46 by khanhayf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
HEAD = pipex.h
SRC = pipex.c pipex_utils1.c pipex_utils2.c
OBJ = pipex.o pipex_utils1.o pipex_utils2.o
CC = cc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o : %.c $(HEAD)
	$(CC) $(FLAGS) -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
