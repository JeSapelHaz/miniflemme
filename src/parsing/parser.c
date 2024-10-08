/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:54:51 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/08 18:44:58 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"



t_node	*str_node(char *str)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = STR_NODE;
	node->data.str = str;
	return (node);
}

t_node	*pair_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = PAIR_NODE;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);
}

static t_node	*ft_parse_pair(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = PAIR_NODE;
	node->data.opera = token->lexeme;
	

}


t_node	*parse(t_token **token_list)
{
	t_token	*tmp;

	tmp = *token_list;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			ft_parse_pair(tmp);
		else if(tmp->type == CHAR_TOKEN)
			return (ft_str_node(tmp->lexeme));
		tmp = tmp->next;
	}
}
