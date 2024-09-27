/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:54:11 by alama             #+#    #+#             */
/*   Updated: 2024/09/26 20:55:14 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	ft_del(t_token *stack)
{
	stack->next = NULL;
	stack->prev = NULL;
	free(stack);
	stack = NULL;
}

void	ft_free_token(t_token **stack)
{
	t_token	*tmp;
	t_token	*s;

	if (!stack || !(*stack))
		return ;
	if ((*stack)->next != NULL)
	{
		s = (*stack)->next;
		while (s != (*stack))
		{
			tmp = s->next;
			ft_del(s);
			s = NULL;
			s = tmp;
		}
	}
	ft_del(*stack);
	*stack = NULL;
}
