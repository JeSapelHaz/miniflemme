/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:37:20 by alama             #+#    #+#             */
/*   Updated: 2024/10/28 19:54:50 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//	"coucou" " " "mdr" " " "|"
//	"coucou "
//	"coucou  mdr"
//	"coucou  mdr "

static void	add_lexeme_to_node(t_token **token, t_node *node)
{
	char	*str;

	str = NULL;
	node->data.str = ft_strdup((*token)->lexeme);
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

t_node	*pair_node(t_node *left, t_token **token)
{
	t_node	*new_node;
	t_node	*right;

	new_node = malloc(sizeof(t_node));
	// if !malloc
	new_node->data.pair.opera = (*token)->lexeme;
	*token = (*token)->next;
	new_node->type = PAIR_NODE;
	new_node->data.pair.left = left;
	right = str_node(token);
	new_node->data.pair.right = right;
	return (new_node);
}

t_node	*str_node(t_token **token)
{
	t_node	*node;

	if (!token || ft_is_dir(*token) == 1)
		return (NULL);
	node = malloc(sizeof(t_node));
	// if !malloc
	left->type = STR_NODE;
	add_lexeme_to_node(token, node);
	printf("left value : %s\n", node->data.str);
	return (node);
}

t_node *parse(t_token **token_list)
{
	t_token	*token;
	t_node	*left;

	token = (*token_list);
	left = str_node(&token);
	printf("token after : %d\n", token->type);
	token = token->next;
	while (token->type != END_TOKEN)
	{
		if (ft_is_dir(token) == 1)
			left = pair_node(left, token);
		token = token->next;
	}
	return (left);
}
