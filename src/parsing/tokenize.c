/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:20:21 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/18 17:15:08 by alama            ###   ########.fr       */
/*   Updated: 2024/10/06 15:45:17 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * ft_add_token - Ajoute un nouveau token à la liste chaînée de tokens.
 *
 * @token: Adresse du pointeur vers la tête de la liste de tokens
 * @type: Type du token à ajouter
 * @lexeme: Lexème du token, qui doit être alloué dynamiquement.
 *
 * La fonction crée un token et l'ajoute à la liste.
 * En cas d'échec d'allocation, elle libère la mémoire existante
 * et termine le programme avec un message d'erreur.
 */
#include <stdlib.h>
#include <stdio.h>

int	nb = 1;

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
	new_token->nb = nb;
	nb++;
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
		&& str[i] != ')' && str[i] != '\"')
	{
		if (type == CHAR_TOKEN && str[i] == ' ')
			break ;
		else
			i++;
	}
	found = 0;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		found = 1;
	lexeme = ft_strndup(&str[start], i - start);
	ft_add_token(token_list, type, lexeme);
	if (type != CHAR_TOKEN)
		i++;
	if (found == 1)
		i--;
	return (i);
}

/**
 * tokenize - Fonction principale qui tokenise toute la chaîne de caractères.
 * Ignorer les espaces en dehors des opérateurs
 * Gestion des différents types de tokens
 * Gestion des strings + lui créer un token
 *
 * @param str: Chaîne de caractères à tokeniser.
 * @return: Liste chaînée de tokens.
 */
t_token	*tokenize(char *str)
{
	t_token *token_list;
	int i;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			ft_add_token(&token_list, END_TOKEN, ft_strdup("\0"));
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
