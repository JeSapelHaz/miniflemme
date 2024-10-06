/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:54:51 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/06 15:42:56 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

// /**
//  * Fonction récursive descendante pour analyser une commande.
//  * Elle retourne un arbre de nœuds représentant la commande.
//  * Si on a un token PIPE, on crée un nœud pour la pipe
//  */
// t_node	*parse_command(t_token **token_list)
// {
// 	t_node	*left;

// 	left = parse_simple_command(token_list);

// 	if (*token_list && ((*token_list)->type == PIPE
// 			|| (*token_list)->type == O_DIR
// 			|| (*token_list)->type == OA_DIR
// 			|| (*token_list)->type == DI_DIR
// 			|| (*token_list)->type == I_DIR))
// 	{
// 		(*token_list) = (*token_list)->next;
// 		t_node *right = parse_command(token_list);
// 		return (create_pair_node(left, right));
// 			// PIPE devient le nœud parent
// 	}
// 	return (left); // Si pas de PIPE,
// retourner juste la commande	gauche(la seule)
// }

// /**
//  * Analyse une simple commande
//  * Un ou plusieurs CHAR_TOKEN
//  * Tant qu'on trouve des tokens de type CHAR_TOKEN,
// 	on continue d'ajouter au nœud
//  */
// t_node	*parse_simple_command(t_token **token_list)
// {
// 	t_node	*root;
// 	t_node	*new_node;

// 	if (!*token_list || (*token_list)->type == END_TOKEN)
// 		return (NULL);
// 	root = create_char_node((*token_list)->lexeme);
// 	*token_list = (*token_list)->next;
// 	while (*token_list && ((*token_list)->type == CHAR_TOKEN
// 			|| (*token_list)->type == PAREN_TOKEN
// 			|| (*token_list)->type == SINGLE_QUOTE
// 			|| (*token_list)->type == DOUBLE_QUOTE))
// 	{
// 		new_node = create_char_node((*token_list)->lexeme);
// 		root = create_pair_node(root, new_node);
// 		*token_list = (*token_list)->next;
// 	}
// 	return (root);
// }

t_node	*create_node(char *str)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str = str;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*parse(t_token **token_list)
{
	int		i;
	t_node	*root;
	char	*str;

	i = 0;
	str = "";
	while (!(*token_list)->type)
	{
		if ((*token_list)->type == PIPE)
		{
			root = create_node(str);
			str = "";
			continue ;
		}
		else
			str = ft_strjoin(str, (*token_list)->lexeme);
		*token_list = (*token_list)->next;
	}
	str = ft_strjoin(str, (*token_list)->lexeme);
	root = create_node(str);
	return (root);
}
