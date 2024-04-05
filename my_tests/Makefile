#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 20:22:45 by tmina-ni          #+#    #+#              #
#    Updated: 2024/04/05 14:15:31 by tmina-ni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tester
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
SRC = $(shell find ../src/ -name "*.c")
LIBFT = -L../libft -lft

all: 
	$(MAKE) -C ../ 
	cp ../minishell ./
	$(CC) $(CFLAGS) tester_minishell.c $(LIBFT) -lrt -lm -o $(NAME) 
	./$(NAME)
	$(MAKE) fclean

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) -lrt -lm $(LIBFT)

#usage example: make hashtable
#tester_$@.c
%:
	$(CC) $(CFLAGS) $(filter-out ../src/main.c, $(SRC)) tester_$@.c $(LIBFT) -lreadline -lrt -lm -o $(NAME) 
	./$(NAME)
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
	rm -f *.o
	rm -f ./files/outfile*

fclean: clean
	rm -f minishell $(NAME)

re: fclean all

.PHONY: all minishell bonus clean fclean re
