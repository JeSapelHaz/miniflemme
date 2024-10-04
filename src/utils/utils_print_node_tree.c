/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_node_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:03 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/04 11:29:18 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	print_indentation(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		printf(" - ");
		i++;
	}
}

/*
 * Si c'est un CHAR_NODE, afficher le caractère ou la commande
 * Si c'est un PAIR_NODE, afficher et descendre récursivement
*/
void	print_node_tree(t_node *node, int level)
{
	if (!node)
		return ;
	print_indentation(level);
	if (node->type == CHAR_NODE)
	{
		printf("CHAR_NODE: %s\n", node->data.c);
	}
	else if (node->type == PAIR_NODE)
	{
		printf("PAIR_NODE:\n");
		print_node_tree(node->data.pair.left, level + 1); // Pour aller un cran en dessous du coté gauche
		print_node_tree(node->data.pair.right, level + 1); // Pour aller un cran en dessous du coté droit
	}
}
