# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:52:47 by hbutt             #+#    #+#              #
#    Updated: 2024/11/20 17:36:57 by alama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

# Project name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror 

# Directories
SRCDIR = src
OBJDIR = .build

# Source files by category
SRC_MAIN = $(SRCDIR)/main.c

SRC_PARSING = $(SRCDIR)/parsing/parser.c \
              $(SRCDIR)/parsing/tokenize.c \
              $(SRCDIR)/parsing/check_args.c \
              $(SRCDIR)/parsing/verrif_token.c \
              $(SRCDIR)/parsing/dir_parser.c

SRC_UTILS = $(SRCDIR)/utils/utils_str.c \
            $(SRCDIR)/utils/utils_token.c \
            $(SRCDIR)/utils/utils_print_node_tree.c \
            $(SRCDIR)/utils/utils_print_tokens.c \
            $(SRCDIR)/utils/utils.c \
            $(SRCDIR)/utils/utils_node.c 

SRC_ENV = $(SRCDIR)/env/get_path.c

SRC_BUILTINS = $(SRCDIR)/builtins/ft_cd.c \
               $(SRCDIR)/builtins/ft_env.c \
               $(SRCDIR)/builtins/ft_exit.c \
               $(SRCDIR)/builtins/ft_pwd.c \
			   $(SRCDIR)/builtins/ft_unset.c \
			   $(SRCDIR)/builtins/ft_export.c \
               $(SRCDIR)/builtins/ft_echo.c

SRC_EXE = $(SRCDIR)/exe/exe.c \
          $(SRCDIR)/exe/path.c \
          $(SRCDIR)/exe/dir_exe.c \
          $(SRCDIR)/exe/dir_choice.c

# All source files and corresponding object files
SRC = $(SRC_MAIN) $(SRC_PARSING) $(SRC_UTILS) $(SRC_ENV) $(SRC_BUILTINS) $(SRC_EXE)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Libraries
LIBFT = ./libft/libft.a

# Compilation rules
all: $(NAME)

# Build executable
$(NAME): $(OBJ) | $(OBJDIR)
	@echo "$(YELLOW)Building libft...$(DEF_COLOR)"
	@make -C ./libft --silent
	@echo "$(YELLOW)Linking $(NAME)...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME) -I./includes -I./libft
	@echo "$(GREEN)$(NAME) compiled successfully!$(DEF_COLOR)"

# Create build directories
$(OBJDIR):
	@mkdir -p $(OBJDIR)/parsing $(OBJDIR)/env $(OBJDIR)/utils $(OBJDIR)/builtins $(OBJDIR)/exe

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./libft
	@echo "$(CYAN)Compiled $(notdir $<)$(DEF_COLOR)"

# Clean up object files
clean:
	@echo "$(RED)Cleaning object files...$(DEF_COLOR)"
	@make clean -C ./libft --silent
	@rm -rf $(OBJDIR)

# Clean up all build files
fclean: clean
	@echo "$(RED)Removing $(NAME)...$(DEF_COLOR)"
	@make fclean -C ./libft --silent
	@rm -f $(NAME)
	@rm -rf *dSYM*

# Rebuild project
re: fclean all

.PHONY: all fclean clean re
