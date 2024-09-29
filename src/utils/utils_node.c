/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:51:39 by hbutt             #+#    #+#             */
/*   Updated: 2024/09/28 21:12:21 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

/**
 * Créer un nouveau nœud.
 */
t_node	*create_char_node(char c)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = CHAR_NODE;
	node->data.c = c;
	return (node);
}

/**
 * Créer un nœud pair (opérateur + commande gauche/droite).
 */
t_node	*create_pair_node(t_node *left, t_node *right)
{
	t_node *node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = PAIR_NODE;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);
}