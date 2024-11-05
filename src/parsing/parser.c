/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:37:20 by alama             #+#    #+#             */
/*   Updated: 2024/11/04 21:12:20 by alama            ###   ########.fr       */
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
			return ;
		}
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

	if (!token || ft_is_dir(*token) == 1)
		return (NULL);
	node = malloc(sizeof(t_node));
	// if !malloc
	node->type = STR_NODE;
	printf("test\n");
	printf("tok : %s\n", (*token)->lexeme);
	add_lexeme_to_node(token, node, pipe);
	printf("test\n");
	return (node);
}

t_node	*pair_node(t_node *left, t_token **token)
{
	t_node	*new_node;
	t_node	*right;
	int		pipe;

	pipe = 1;
	new_node = malloc(sizeof(t_node));
	// if !malloc
	new_node->data.pair.opera = (*token)->lexeme;
	if ((*token)->type == PIPE && left->type == STR_NODE)
	{
		pipe = 0;
		left = left_before_pipe(left, token);
	}
	*token = (*token)->next;
	new_node->type = PAIR_NODE;
	new_node->data.pair.left = left;
	right = str_node(token, 0);
	new_node->data.pair.right = right;
	return (new_node);
}

t_node	*parse(t_token **token_list)
{
	t_token	*token;
	t_node	*left;

	token = (*token_list);
	left = NULL;
	left = left_before_pipe(left, &token);
	token = token->next;
	while (token && token->type != END_TOKEN)
	{
		if (token->type == PIPE)
		{
			left = pair_node(left, &token);
		}
		token = token->next;
	}
	printf("here or not here\n");
	return (left);
}

void	print_node(t_node *node)
{
	if (node->type == STR_NODE)
		printf("node : %s\n", node->data.str);
	else
	{
		printf("operator : %s\n", node->data.pair.opera);
		print_node(node->data.pair.left);
		print_node(node->data.pair.right);
	}
}
