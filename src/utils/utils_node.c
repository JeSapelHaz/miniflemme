/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:51:39 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/05 13:57:39 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_free_node(t_node **node)
{
	if (*node)
	{
		if (((*node)->type) == PAIR_NODE)
		{
			(*node)->data.pair.left = NULL;
			(*node)->data.pair.right = NULL;
			free((*node)->data.pair.opera);
			free(*node);
			return ;
		}
		free((*node)->data.str);
		free(*node);
	}
}

t_node	*left_before_pipe(t_node *left, t_token **token)
{
	t_node	*l;
	t_token	*tok;
	
	tok = (*token);
	printf("\n\n\n\n");
	printf("ici ----> %s\n", tok->lexeme);
	if (left != NULL)
		tok = tok->prev;
	while (tok->prev != NULL && tok->type != PIPE)
		tok = tok->prev;
	l = str_node(&tok, 0);
	tok = tok->next;
	while (tok && (tok->type != PIPE && tok->type != END_TOKEN))
	{
		if (ft_is_dir(tok) == 1)
			l = pair_node(l, &tok);
		tok = tok->next;
	}
	ft_free_node(&left);
	return (l);
}
/*
t_node	*right_after_pipe(t_token **token)
{
	t_node	*left;

	if (is_there_dir(*token) == 0)
		return (str_node(token, 1));
	left = str_node(token, 0);
	while ((*token) && (*token)->type != PIPE)
	{
		if (ft_is_dir(*token) == 1 && (*token)->type != PIPE)
			left = pair_node(left, token);
		*token = (*token)->next;
	}
	return (left);
}
*/
