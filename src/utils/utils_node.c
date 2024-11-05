/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:51:39 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/04 21:55:00 by alama            ###   ########.fr       */
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

int		is_there_dir(t_token *tok)
{
	while (tok)
	{
		if (ft_is_dir(tok) == 1)
			return (1);
		tok = tok->prev;
	}
	return (0);
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

t_node	*right_before_pipe(t_token **token)
{
	t_node	*right;

	while ((*token)->type != PIPE || (*token)->type != END_TOKEN)
	{
		
	}
}
