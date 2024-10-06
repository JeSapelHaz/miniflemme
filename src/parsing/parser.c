/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:54:51 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/06 18:26:15 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_node	*create_node(t_node_type type, char **args)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		perror("Failed to allocate memory for tree node");
		exit(EXIT_FAILURE);
	}
	new_node->type = type;
	new_node->args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
t_node *parse_left(t_token **token_list)
{
	t_node *node;
	char **args;
	args = malloc(sizeof(char *)* 2 + 1);
	args[0] = malloc(sizeof((*token_list)->prev->lexeme)); 
	args[1] = malloc(sizeof((*token_list)->prev->prev->lexeme)); 
	args[0] = (*token_list)->prev->lexeme; 
	args[1] = (*token_list)->prev->prev->lexeme; 
	node = create_node(COMMAND_NODE, args);
	node->type = COMMAND_NODE;

	return node;
}

t_node *parse(t_token **token_list)
{
	t_node *root;

	while(*token_list)
	{
		if((*token_list)->type == PIPE)
		{
			root = create_node(PIPELINE_NODE, NULL);
			root->right = parse(token_list);
		}
	}
	root->left = parse_left(token_list);
	return root;
}