/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:16:36 by alama             #+#    #+#             */
/*   Updated: 2024/11/05 17:12:50 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_node	*pair_dir(t_node *left, t_token **token)
{
	t_node	*new_node;
	t_node	*right;

	new_node = malloc(sizeof(t_node));
	//if node
	new_node->data.pair.opera = (*token)->lexeme;
	new_node->type = PAIR_NODE;
	new_node->data.pair.left = left;
	*token = (*token)->next;
	right = str_node(token, 0);
	new_node->data.pair.right = right;
	return (new_node);
}

t_node	*dir_parse(t_token **token)
{
	t_node	*left;

	left = str_node(token, 0);
	while (*token && (*token)->type != PIPE && 
		(*token)->type != END_TOKEN)
	{
		if (ft_is_dir(*token) == 1)
			left = pair_dir(left, token);
		*token = (*token)->next;
	}
	printf("token after dir parse : %s\n", (*token)->lexeme);
	printf("what is the pipe : %s\n", left->data.pair.opera);
	return (left);
}
