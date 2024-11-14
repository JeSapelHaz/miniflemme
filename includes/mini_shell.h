/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:43 by alama             #+#    #+#             */
/*   Updated: 2024/11/14 18:09:40 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "builtins.h"
# include "ft_exe.h"
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Fonctions de gestion des arguments
/* CHECK ARGS */
void	check_args(int ac, char **av);

// Fonction pour quitter
void	ft_quit(void);

// Fonctions de tokenisation
void	ft_add_token(t_token **token, t_token_type type, char *lexeme);
t_token	*tokenize(char *str);

// Fonctions de parsing
t_node	*parse(t_token **token_list);

// Fonctions de gestion de l'environnement
char	*get_path(char *cmd, char **env);

// Exécution des commandes
void	execute_commands(char *input, char **env);

// Fonctions utilitaires générales
void	ft_quit(void);

void	print_token_list(t_token *token_list);
void	print_node(t_node *node);

// Fonctions utilitaires sur les noeuds
void	execute_node(t_node *node);
t_node	*str_node(t_token **token, int pipe);
t_node	*pair_node(t_node *left, t_token **token);
void	ft_free_node(t_node **node);
t_node	*dir_parse(t_token **token);
t_node	*pari_dir(t_node *left, t_token **token);

// Fonctions utilitaires pour les tokens
void	ft_if_not_last(t_token **token_list, t_token **new_node);
void	ft_add_next(t_token *last, t_token **token_list, t_token *new_node);
void	ft_free_token(t_token **token_list);
void	remove_end(t_token **token);
t_token	*last_token(t_token *token);
char	*ft_last_pipe(t_token **token_list, char *str);
int		ft_verrif_tok(t_token **token_list);
int		ft_is_dir(t_token *token);

// Fonctions utilitaires pour les chaînes
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strdel(char *str, const char *del);

// Gestion des signaux
void	ft_handle_signals(int signal);

// Fonctions pour gérer le texte de readline
void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

// Construction et exécution des arbres de commandes
t_node	*build_command_tree(t_token *tokens);

#endif