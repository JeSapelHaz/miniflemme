/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:43 by alama             #+#    #+#             */
/*   Updated: 2024/10/05 15:57:56 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "token.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

/* CHECK ARGS */
void		check_args(int ac, char **av);

/* ERROR */
void	ft_quit(void);

/* TOKENIZE */
void	ft_add_token(t_token **token, t_token_type type, char *lexeme);
t_token	*tokenize(char *str);


/* PARSING */
t_node	*parse_simple_command(t_token **token_list);
t_node	*parse_command(t_token **token_list);

/* ENV */
char	*get_path(char *cmd, char **env);

/* EXEC COMMANDES */
void execute_commands(char *input, char **env);


/* UTILS */
void	ft_quit(void);

/* UTILS PRINT */
void	print_node_tree(t_node *node, int level);

/* UTILS NODE */
t_node	*create_char_node(char *c);
t_node	*create_pair_node(t_node *left, t_node *right);

/* UTILS TOKEN */
void	ft_if_not_last(t_token **token_list, t_token **new_node);
void	ft_add_next(t_token *last, t_token **token_list, t_token *new_node);
// void	find_last_token(t_token **token_list);
void	ft_free_token(t_token **token_list);

/* UTILS STR */
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);

/* SIGNAL */
void	ft_handle_signals(int signal);

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

t_node *build_command_tree(t_token *tokens);

#endif
