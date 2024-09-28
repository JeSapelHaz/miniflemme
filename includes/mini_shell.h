/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:43 by alama             #+#    #+#             */
/*   Updated: 2024/09/28 17:40:19 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "token.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_node_type
{
	PAIR_NODE,
	CHAR_NODE
}						t_node_type;

typedef struct s_node	t_node;

typedef struct s_pair_value
{
	t_node				*left;
	t_node				*right;
}						t_pair_value;

typedef union u_node_value
{
	t_pair_value		pair;
	char				c;
}						t_node_value;

struct					s_node
{
	t_node_type			type;
	t_node_value		data;
};

/* TOKENIZE */
void					ft_add_token(t_token **token, t_token_type type,
							char *lexeme);
t_token					*tokenize(char *str);
void					ft_free_token(t_token **stack);

/* UTILS TOKEN */
void				ft_if_not_last(t_token **stack, t_token **new_node);
void				ft_add_next(t_token *last, t_token **stack,
							t_token *new_node);

/* UTILS STR */
int						ft_strcmp(char *s1, char *s2);
char					*ft_strdup(const char *src);
char					*ft_strndup(const char *src, size_t n);

#endif
