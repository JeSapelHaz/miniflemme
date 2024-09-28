/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:20:21 by hbutt             #+#    #+#             */
/*   Updated: 2024/09/28 16:21:47 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_add_token(t_token **token, t_token_type type, char *lexeme);

/**
 * tokenize - Fonction principale qui tokenise toute la chaîne de caractères.
 * @param str: Chaîne de caractères à tokeniser.
 * @return: Liste chaînée de tokens.
 */
t_token *tokenize(char *str)
{
    t_token *token_list = NULL;  // Pointeur vers la liste de tokens
    int i = 0;

    while (str[i])
    {
        // Ignorer les espaces en dehors des opérateurs
        if (str[i] == ' ')
        {
            i++;
            continue;
        }

        // Gestion des différents types de tokens
        if (str[i] == '\n')
            ft_add_token(&token_list, END_TOKEN, strdup("\n"));
        else if (str[i] == '|')
            ft_add_token(&token_list, PIPE, strdup("|"));
        else if (str[i] == '>')
            ft_add_token(&token_list, O_DIR, strdup(">"));
        else if (str[i] == '<')
            ft_add_token(&token_list, I_DIR, strdup("<"));
        else if (str[i] == '(')
            ft_add_token(&token_list, LPARAN_TOKEN, strdup("("));
        else if (str[i] == ')')
            ft_add_token(&token_list, RPARAN_TOKEN, strdup(")"));
        else if (str[i] == '\'')
            ft_add_token(&token_list, SINGLE_QUOTE, strdup("'"));
        else if (str[i] == '\"')
            ft_add_token(&token_list, DOUBLE_QUOTE, strdup("\""));
        else
        {
            // Traitement des séquences de caractères (commandes, arguments)
            int start = i;
            while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '|' 
				&& str[i] != '>' && str[i] != '<' && str[i] != '(' && str[i] != ')')
                i++;
            // Créer un token pour la séquence trouvée
            char *lexeme = strndup(&str[start], i - start);
            ft_add_token(&token_list, CHAR_TOKEN, lexeme);
            continue;  // Éviter l'incrémentation supplémentaire de i
        }
        i++;
    }
    return token_list;  // Retourner la liste chaînée de tokens
}

