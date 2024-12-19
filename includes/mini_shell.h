/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:43 by alama             #+#    #+#             */
/*   Updated: 2024/12/16 18:47:35 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft.h"
# include <stdio.h>
# include "token.h"
# include "ft_exe.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* exite code 8*/
extern int	excode;

/* CHECK ARGS */
void	check_args(int ac, char **av);

/* ERROR */
void	ft_quit(void);

/* TOKENIZE */
void	ft_add_token(t_token **token, t_token_type type, char *lexeme);
t_token	*tokenize(char *str);

/* PARSING */
t_node	*parse(t_token **token_list);

/* UTILS */
int	only_space(char *str);
void	ft_quit(void);

/* UTILS PRINT */
void	print_token_list(t_token *token_list);
void	print_node(t_node *node);

/* UTILS NODE */
t_node	*parse(t_token **token_list);
void	execute_node(t_node *node);
t_node	*str_node(t_token **token, int pipe);
t_node	*pair_node(t_node *left, t_token **token);
void	ft_free_node(t_node **node);
t_node	*dir_parse(t_token **token);
t_node	*pair_dir(t_node *left, t_token **token);
void	ft_free_all_node(t_node **node);
t_node	*set_right_file(t_token **token, t_node *left);
void	heredoc_parse(t_token **token);
void	set_right_space(t_node *left, t_node *right);
t_node	*one_str(t_token **token);
void	add_dollar(t_node *node, char **env);

/* UTILS TOKEN */
void	ft_if_not_last(t_token **token_list, t_token **new_node);
void	ft_add_next(t_token *last, t_token **token_list, t_token *new_node);
int		ft_str_to_lexeme(int i, char *str, t_token **tok, t_token_type type);
void	ft_free_token(t_token **token_list);
void	remove_end(t_token **token);
t_token	*last_token(t_token *token);
char	*ft_last_pipe(t_token **token_list, char *str);
int		ft_verrif_tok(t_token **token_list);
int		ft_is_dir(t_token *token);
void	ft_not_close(char c);
int		d_and_s_token(int i, char *str, t_token **token_list);
t_token	*find_pipe(t_token *token_list);

/* UTILS STR */
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strdel(char *str, const char *del);


void rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

t_node	*build_command_tree(t_token *tokens);

/* ENV */
char **copy_env(char **env);

// Prototype des fonctions builtins
void	ft_cd(char **args);
void	ft_echo(char **args);
void	ft_env(char **args, char **env);
void	ft_export(char **args, char ***env);
void	ft_exit(char **args);
void	ft_pwd(char **args);
void	ft_unset(char **args, char ***env);

void	handle_sigquit(int sig);
void	handle_sigint(int signal);

void	initialize_signals(void);
void	replace_env_in_nodes(t_node *node, char **env);
char *remove_backslashes(const char *str);
void clean_str_nodes(t_node *node);


typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

#endif
