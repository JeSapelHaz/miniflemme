/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:20:21 by hbutt             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/07 15:53:47 by hbutt            ###   ########.fr       */
=======
/*   Updated: 2024/10/08 18:42:09 by alama            ###   ########.fr       */
/*   Updated: 2024/10/06 15:45:17 by hbutt            ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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
void ft_add_token(t_token **token_list, t_token_type type, char *lexeme) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token) {
        perror("Failed to allocate memory for token");
        ft_free_token(token_list);
        exit(EXIT_FAILURE);
    }
    
    // Initialisation du nouveau token
    new_token->type = type;
    new_token->lexeme = lexeme;
    new_token->next = NULL;
    new_token->prev = NULL;

    // Si la liste est vide, le nouveau token devient le premier
    if (!*token_list) {
        *token_list = new_token;
        return;
    }

    // Parcours de la liste pour trouver le dernier élément
    t_token *last = *token_list;
    while (last->next) {
        last = last->next;
    }

    // Ajout du nouveau token à la fin de la liste
    last->next = new_token;
    new_token->prev = last;
}


static int	ft_str_to_lexeme(int i, char *str, t_token **token_list, t_token_type type)
{
	int		start;
	char	*lexeme;

	if (type != CHAR_TOKEN)
		i++;
	start = i;
	while (str[i] && str[i] != '\n' && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && str[i] != ')' && str[i] != '\"')
	{
		if (type == CHAR_TOKEN && str[i] == ' ')
			break ;
		else
			i++;
	}
	lexeme = ft_strndup(&str[start], i - start);
	ft_add_token(token_list, type, lexeme);
	if (type != CHAR_TOKEN)
		i++;
	return (i);
}

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	handle_redirections(char *str, int i, t_token **token_list)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			ft_add_token(token_list, OA_DIR, ft_strdup(">>"));
			return (i + 2);
		}
		else
		{
			ft_add_token(token_list, O_DIR, ft_strdup(">"));
			return (i + 1);
		}
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			ft_add_token(token_list, DI_DIR, ft_strdup("<<"));
			return (i + 2);
		}
		else
		{
			ft_add_token(token_list, I_DIR, ft_strdup("<"));
			return (i + 1);
		}
	}
	return (i);
}

int	handle_special_chars(char *str, int i, t_token **token_list)
{
	if (str[i] == '|')
	{
		ft_add_token(token_list, PIPE, ft_strdup("|"));
		return (i + 1);
	}
	else if (str[i] == '(' || str[i] == ')')
	{
		ft_add_token(token_list, PAREN_TOKEN, ft_strndup(&str[i], 1));
		return (i + 1);
	}
	return (i);
}

int	handle_quotes(char *str, int i, t_token **token_list)
{
	if (str[i] == '\'')
		return (ft_str_to_lexeme(i, str, token_list, SINGLE_QUOTE));
	else if (str[i] == '\"')
		return (ft_str_to_lexeme(i, str, token_list, DOUBLE_QUOTE));
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
	t_token	*token_list;
	int		i;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		i = handle_special_chars(str, i, &token_list);
		i = handle_redirections(str, i, &token_list);
		i = handle_quotes(str, i, &token_list);
		if (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>'
			&& str[i] != '<' && str[i] != '(' && str[i] != ')' && str[i] != '\''
			&& str[i] != '\"')
			i = ft_str_to_lexeme(i, str, &token_list, CHAR_TOKEN);
	}
	ft_add_token(&token_list, END_TOKEN, ft_strdup("\0"));
	return (token_list);
}
