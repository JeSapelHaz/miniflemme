/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:51:39 by hbutt             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/21 16:42:01 by alama            ###   ########.fr       */
=======
/*   Updated: 2024/11/22 14:30:29 by hbutt            ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

<<<<<<< HEAD
void	ft_free_node(t_node **node)
{
	if (*node)
	{
		if (((*node)->type) == PAIR_NODE)
		{
			(*node)->data.pair.left = NULL;
			(*node)->data.pair.right = NULL;
			if ((*node)->data.pair.opera)
				free((*node)->data.pair.opera);
			free(*node);
			return ;
		}
		if ((*node)->data.str)
			free((*node)->data.str);
		free(*node);
	}
}

void	ft_free_all_node(t_node **node)
{
	if (!node || !(*node))
		return ;
	if ((*node)->type == STR_NODE)
		ft_free_node(node);
	else
	{
		ft_free_all_node(&(*node)->data.pair.left);
		ft_free_all_node(&(*node)->data.pair.right);
		ft_free_node(node);
	}
}

t_node	*left_before_pipe(t_node *left, t_token **token)
{
	t_node	*l;
	t_token	*tok;

	tok = (*token);
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
=======
>>>>>>> master
