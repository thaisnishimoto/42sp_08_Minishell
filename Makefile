# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmina-ni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 14:02:42 by tmina-ni          #+#    #+#              #
#    Updated: 2024/04/15 10:31:31 by tmina-ni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#================================FLAGS=========================================#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_FLAG = -L$(LIB_PATH) -lft
MAKE_NO_PRINT = $(MAKE) --no-print-directory

#================================PATHS=========================================#

LIB_PATH = ./libft/
SRC_PATH = ./src
HEADER_PATH = ./include

#================================FILES=========================================#

NAME = minishell
#SRC = $(wildcard $(SRC_PATH)/*.c)
SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)
HEADER = $(HEADER_PATH)/minishell.h

#================================RULES=========================================#

all: libft $(NAME)

libft:
	$(MAKE_NO_PRINT) -C $(LIB_PATH)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_FLAG) -lreadline

$(SRC_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

leak: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp --suppressions=42readline.supp ./$(NAME)
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=readline.supp ./$(NAME)

#================================CLEAN=========================================#

clean:
	rm -f $(OBJ)
	$(MAKE_NO_PRINT) clean -C $(LIB_PATH)

fclean: clean
	rm -f $(NAME)
	$(MAKE_NO_PRINT) fclean -C $(LIB_PATH)

re: fclean all

.PHONY: all libft clean fclean re
