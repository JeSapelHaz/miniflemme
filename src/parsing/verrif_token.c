/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verrif_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:50:36 by alama             #+#    #+#             */
/*   Updated: 2024/10/21 19:13:11 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_is_dir(t_token *token)
{
	if ((token->type == PIPE || token->type == O_DIR || token->type == I_DIR
			|| token->type == OA_DIR || token->type == DI_DIR)
		&& token->type != END_TOKEN)
		return (1);
	return (0);
}

int	ft_verrif_tok(t_token **token_list)
{
	t_token	*tmp;

	if (!token_list || !*token_list)
		return (1);
	tmp = *token_list;
	while (tmp->next->type != END_TOKEN)
	{
		if (ft_is_dir(tmp) == 1)
		{
			if (tmp->next->type == 2)
				tmp = tmp->next;
			if (ft_is_dir(tmp->next) == 1)
			{
				printf("mini-flemme: syntax error near unexpected token `%s'\n", tmp->next->lexeme);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	if (ft_is_dir(*token_list) == 1)
	{
		if ((*token_list)->type != PIPE)
			printf("mini-flemme: syntax error near unexpected token `newline'\n");
		else
			printf("mini-flemme: syntax error near unexpected token `|'\n");
		ft_free_token(token_list);
		return (1);
	}
	return (0);
}
