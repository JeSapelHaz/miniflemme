# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:52:47 by hbutt             #+#    #+#              #
#    Updated: 2024/09/22 17:52:12 by alama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = src/start/main.c src/parsing/parser.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = ./libft/libft.a

SRC_DIR = src

OBJ_DIR = .cache

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft 1>/dev/null
	@$(CC) $(CFLAGS) -o $(NAME) $(PRINTF) $(LIBFT) $(SRC) -I./includes -I./libft
	@echo "Compilation successful!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/start
	@mkdir -p $(OBJ_DIR)/parsing

clean:
	@make clean -C ./libft 1>/dev/null
	@rm -rf $(OBJ_DIR)/start
	@rm -rf $(OBJ_DIR)/parsing

fclean: clean
	@make fclean -C ./libft 1>/dev/null
	@rm -f $(NAME) *.o
	@rm -rf *dSYM*

re: fclean $(NAME)

.PHONY: all fclean clean re 
