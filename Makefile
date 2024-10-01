# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:52:47 by hbutt             #+#    #+#              #
#    Updated: 2024/10/01 17:14:53 by hbutt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c src/parsing/parser.c src/parsing/tokenize.c src/utils/utils_str.c \
src/utils/utils_token.c src/utils/utils_print_node_tree.c  src/utils/utils_node.c \
src/parsing/check_args.c src/env/get_path.c src/utils/utils.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = ./libft/libft.a

SRC_DIR = src

OBJ_DIR = .build

all: $(NAME)

$(NAME): $(OBJ) | $(OBJ_DIR)
	@make -C ./libft 1>/dev/null
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $(PRINTF) $(LIBFT) $(SRC) -I./includes -I./libft
	@echo "$(MAGENTA)Compilation successful!"

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
