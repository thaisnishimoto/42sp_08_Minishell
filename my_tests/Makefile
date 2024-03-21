#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 20:22:45 by tmina-ni          #+#    #+#              #
#    Updated: 2024/03/21 15:33:50 by tmina-ni         ###   ########.fr        #
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
	$(CC) $(CFLAGS) $(filter-out ../src/main.c, $(wildcard ../src/*.c)) tester_$@.c $(LIBFT) -lrt -lm -o $(NAME) 
	./$(NAME)
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
	rm -f *.o
	rm -f outfile*

fclean: clean
	rm -f minishell $(NAME)

re: fclean all

.PHONY: all minishell bonus clean fclean re
