/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:20:21 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/25 17:36:37 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void ft_add_token(t_token **token, t_token_type type, char *lexeme)
{
	t_token *new_token;
	t_token *last;
	
	new_token = malloc(sizeof(t_token));
	if (!new_token) 
	{
		ft_free_token(token);
		exit(printf("malloc from tokens fails\n"));
	}
	new_token->type = type;
	new_token->lexeme = lexeme;
	new_token->next = NULL;
	if (!token || !*token) 
	{
		new_token->prev = NULL;
		*token = new_token;
		return;
	}
	last = *token;
	while (last->next != NULL) 
	{
		last = last->next;
	}
	last->next = new_token;
	new_token->prev = last;
}

static int	ft_str_to_lexeme(int i, char *str, t_token **token_list, t_token_type type)
{
	int		start;
	char	*lexeme;
	int		found;
	
	if (type != CHAR_TOKEN)
		i++;
	start = i;
	while (str[i] && str[i] != '\n' && str[i] != '|'
		&& str[i] != '>' && str[i] != '<'
		&& str[i] != ')' && str[i] != '\"' && str[i] != '\'')
	{
		if (type == CHAR_TOKEN && str[i] == ' ')
			break ;
		else
			i++;
	}
	found = 0;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<' || str[i] == ' ')
		found = 1;
	lexeme = ft_strndup(&str[start], i - start);
	ft_add_token(token_list, type, lexeme);
	if (found == 1)
		i--;
	return (i);
}

t_token	*tokenize(char *str)
{
	t_token	*token_list;
	int		i;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			ft_add_token(&token_list, SPACE_TOKEN, ft_strdup(" "));
		else if (str[i] == '|')
			ft_add_token(&token_list, PIPE, ft_strdup("|"));
		else if (str[i] == '(')
		{
			i = ft_str_to_lexeme(i, str, &token_list, PAREN_TOKEN);
			if (str[i - 1] != ')')
				return (NULL);
			continue ;
		}
		else if (str[i] == '\'')
			i = ft_str_to_lexeme(i, str, &token_list, SINGLE_QUOTE);
		else if (str[i] == '\"')
			i = ft_str_to_lexeme(i, str, &token_list, DOUBLE_QUOTE);
		else if (str[i] == '>' && str[i + 1] != '>')
			ft_add_token(&token_list, O_DIR, ft_strdup(">"));
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			ft_add_token(&token_list, OA_DIR, ft_strdup(">>"));
			i++;
		}
		else if (str[i] == '<' && str[i + 1] != '<')
			ft_add_token(&token_list, I_DIR, ft_strdup("<"));
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			ft_add_token(&token_list, DI_DIR, ft_strdup("<<"));
			i++;
		}
		else
			i = ft_str_to_lexeme(i, str, &token_list, 1);
		i++;
	}
	ft_add_token(&token_list, END_TOKEN, ft_strdup("\0"));
	return (token_list);
}
