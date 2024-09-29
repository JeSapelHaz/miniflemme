/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:54:11 by alama             #+#    #+#             */
/*   Updated: 2024/09/29 20:33:19 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	ft_del(t_token *token_list)
{
	token_list->next = NULL;
	token_list->prev = NULL;
	free(token_list);
	token_list = NULL;
}
/** 
 * elle libère la mémoire existante 
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
