/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:33:46 by hbutt             #+#    #+#             */
/*   Updated: 2024/09/28 17:42:48 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_add_next(t_token *last, t_token **stack, t_token *new_node)
{
	while (last->next != *stack)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	(*stack)->prev = new_node;
}

void	ft_if_not_last(t_token **stack, t_token **new_node)
{
	(*stack)->next = *new_node;
	(*stack)->prev = *new_node;
	(*new_node)->prev = *stack;
}