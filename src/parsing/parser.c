/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:37:20 by alama             #+#    #+#             */
/*   Updated: 2024/11/08 20:45:08 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//	"coucou" " " "mdr" " " "|"
//	"coucou "
//	"coucou  mdr"
//	"coucou  mdr "

static void	add_lexeme_to_node(t_token **token, t_node *node, int pipe)
{
	char	*str;

	str = NULL;
	node->data.str = ft_strdup((*token)->lexeme);
	if (pipe == 1)
	{
		while ((*token)->type != 0 && (*token)->next->type != PIPE)
		{
			str = ft_strjoin(node->data.str, (*token)->next->lexeme);
			free(node->data.str);
			node->data.str = ft_strdup(str);
			free(str);
			*token = (*token)->next;
		}
		return ;
	}
	while (ft_is_dir(*token) == 0 && ((*token)->next->type != END_TOKEN 
			&& ft_is_dir((*token)->next) == 0))
	{
		str = ft_strjoin(node->data.str, (*token)->next->lexeme);
		free(node->data.str);
		node->data.str = ft_strdup(str);
		free(str);
		*token = (*token)->next;
	}
}

t_node	*str_node(t_token **token, int pipe)
{
	t_node	*node;

	if (!token ||(*token)->type == END_TOKEN || ft_is_dir(*token) == 1)
		return (NULL);
	node = malloc(sizeof(t_node));
	// if !malloc
	node->type = STR_NODE;
	add_lexeme_to_node(token, node, pipe);
	return (node);
}

t_node	*pair_node(t_node *left, t_token **token)
{
	t_node	*new_node;
	t_node	*right;

	new_node = malloc(sizeof(t_node));
	// if !malloc
	new_node->data.pair.opera = (*token)->lexeme;
	//if ((*token)->type == PIPE && left->type == STR_NODE)
	//	left = left_before_pipe(left, token);
	*token = (*token)->next;
	new_node->type = PAIR_NODE;
	new_node->data.pair.left = left;
	right = dir_parse(token);
	//right = left_before_pipe(right, token);
	new_node->data.pair.right = right;
	return (new_node);
}

t_node	*parse(t_token **token_list)
{
	t_token	*token;
	t_node	*left;

	token = (*token_list);
	left = NULL;
	left = dir_parse(&token);
	//token = token->next;
	while (token && token->type != END_TOKEN)
	{
		if (token->type == PIPE)
		{
			left = pair_node(left, &token);
			token = token->prev;
		}
		token = token->next;
	}
	return (left);
}

void	print_node(t_node *node)
{
/*
	printf("left node : %s\n", node->data.pair.left->data.pair.opera);
	printf("operator : %s\n", node->data.pair.opera);
	printf("right node : %s\n", node->data.pair.right->data.str);
*/
	if (node->type == STR_NODE)
		printf("node : %s\n", node->data.str);
	else
	{
		printf("operator : %s\n", node->data.pair.opera);
		if (node->data.pair.left)
			print_node(node->data.pair.left);
		if (node->data.pair.right)
		print_node(node->data.pair.right);
	}
}
