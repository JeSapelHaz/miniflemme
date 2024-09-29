# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:52:47 by hbutt             #+#    #+#              #
#    Updated: 2024/09/29 18:10:49 by hbutt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c src/parsing/parser.c src/parsing/ft_free_token.c src/parsing/tokenize.c src/utils/utils_str.c \
src/utils/utils_token.c src/utils/utils_print_node_tree.c  src/utils/utils_node.c src/parsing/parser2.c src/parsing/check_args.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = ./libft/libft.a

SRC_DIR = src

OBJ_DIR = .build

all: $(NAME)

$(NAME): $(OBJ) | $(OBJ_DIR)
	@make -C ./libft 1>/dev/null
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $(PRINTF) $(LIBFT) $(SRC) -I./includes -I./libft
	@echo "Compilation successful!"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/start
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./libft


clean:
	@make clean -C ./libft 1>/dev/null
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C ./libft 1>/dev/null
	@rm -f $(NAME) *.o
	@rm -rf *dSYM*

re: fclean $(NAME)

.PHONY: all fclean clean re 
