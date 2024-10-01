/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:33:46 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/01 15:09:25 by hbutt            ###   ########.fr       */
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

static void	ft_del(t_token *token_list)
{
	token_list->next = NULL;
	token_list->prev = NULL;
	free(token_list);
	token_list = NULL;
}
/** 
 * elle libère la mémoire existante de la liste de token 
 */
void	ft_free_token(t_token **token_list)
{
	t_token	*tmp;
	t_token	*s;

	if (!token_list || !(*token_list))
		return ;
	if ((*token_list)->next != NULL)
	{
		s = (*token_list)->next;
		while (s != (*token_list))
		{
			tmp = s->next;
			ft_del(s);
			s = NULL;
			s = tmp;
		}
	}
	ft_del(*token_list);
	*token_list = NULL;
}

// void	find_last_token(t_token **token_list)
// {
// 	if (!token_list)
// 		return (NULL);
// 	t_token *current = token_list;
// 	while (current->next && current->next != token_list)
// 	{
// 		current = current->next;
// 	}
// 	return (current);
// }