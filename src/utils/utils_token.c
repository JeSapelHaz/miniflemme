/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:33:46 by hbutt             #+#    #+#             */
/*   Updated: 2024/09/29 20:33:43 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_add_next(t_token *last, t_token **token_list, t_token *new_node)
{
	while (last->next != *token_list)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	(*token_list)->prev = new_node;
}

void	ft_if_not_last(t_token **token_list, t_token **new_node)
{
	(*token_list)->next = *new_node;
	(*token_list)->prev = *new_node;
	(*new_node)->prev = *token_list;
}

void	find_last_token(t_token **token_list)
{
	if (!token_list)
		return (NULL);

	t_token *current = token_list;
	while (current->next && current->next != token_list)
	{
		current = current->next;
	}

	return (current);
}