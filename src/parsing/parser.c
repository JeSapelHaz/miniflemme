/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:37:20 by alama             #+#    #+#             */
/*   Updated: 2024/10/25 17:34:42 by hbutt            ###   ########.fr       */
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
	t_token	*tok;

	str = NULL;
	tok = *token;
	node->data.str = ft_strdup(tok->lexeme);
	printf("%s\n", node->data.str);
	while (ft_is_dir(tok) == 0 && ft_is_dir(tok->next) == 0)
	{
		str = ft_strjoin(node->data.str, tok->next->lexeme);
		free(node->data.str);
		node->data.str = ft_strdup(str);
		free(str);
		tok = tok->next;
	}
}
t_node	*pair_node(t_node *left, t_node *right, t_token *token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	// if !malloc
	new_node->type = PAIR_NODE;
	new_node->data.pair.left = left;
	new_node->data.pair.right = right;
	new_node->data.pair.opera = token->lexeme;
	return (new_node);
}

t_node	*left_node(t_token *token)
{
	t_node	*left;

	if (!token || ft_is_dir(token) == 1)
		return (NULL);
	left = malloc(sizeof(t_node));
	// if !malloc
	left->type = STR_NODE;
	add_lexeme_to_node(&token, left);
	printf("left value : %s\n", left->data.str);
	return (left);
}

t_node *parse(t_token **token_list)
{
	//t_node	*node;
	//t_token	*token;
	t_node	*left;

	left = left_node(*token_list);
	/*
	token = (*token_list);
	while (token->type != END_TOKEN)
	{
		if (ft_is_dir(token) == 1)
		{
		

		}
	}
	*/
	return (left);
}
