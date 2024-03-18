#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 20:22:45 by tmina-ni          #+#    #+#              #
#    Updated: 2024/03/15 17:58:39 by tmina-ni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tester
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
SRC = $(wildcard *.c)
LIBFT = -L../libft -lft

all: minishell $(NAME)
	./$(NAME)
	make --no-print fclean

minishell:
	$(MAKE) -C ../ 
	cp ../minishell ./

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) -lrt -lm $(LIBFT)

#usage example: make hashtable
#tester_$@.c
%:
	$(CC) $(CFLAGS) ../src/$(wildcard ../src/*$@*.c) $(wildcard *$@*.c) $(LIBFT) -lrt -lm -o program 
	./program

clean:
	rm -f *.o
	rm minishell program
	rm -f outfile*

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all minishell bonus clean fclean re
