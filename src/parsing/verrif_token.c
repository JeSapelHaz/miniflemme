/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verrif_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:50:36 by alama             #+#    #+#             */
/*   Updated: 2024/11/08 20:26:39 by alama            ###   ########.fr       */
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

static int	first_verrif(t_token *token)
{
	if (token->type == PIPE)
	{
		printf("mini-flemme: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (ft_is_dir(token) == 1)
	{
		token = token->next;
		while (token->type == SPACE_TOKEN)
	    	token = token->next;
		if (token->type == END_TOKEN)
		{
			printf("mini-flemme: syntax error near unexpected token `newline'\n");
		    return (1);
		}
	}
	return (0);
}

static int	last_verrif(t_token *token)
{
	while (token->type != END_TOKEN)
		token = token->next;
	if (token->type == END_TOKEN)
		token = token->prev;
	while (token->type == SPACE_TOKEN && token->prev != NULL)
		token = token->prev;
	if (token->type == PIPE)
		return (0);
	if (ft_is_dir(token) == 1)
	{
			printf("mini-flemme: syntax error near unexpected token `newline'\n");
			return (1);
	}
	return (0);
}

int	ft_verrif_tok(t_token **token_list)
{
	t_token	*tmp;
	t_token	*last_dir;

	if (!token_list || !*token_list)
		return (1);
	if (first_verrif(*token_list) == 1)
		return (1);
	tmp = *token_list;
	while (tmp->next->type != END_TOKEN)
	{
		if (ft_is_dir(tmp) == 1)
		{
			last_dir = tmp;
			tmp = tmp->next;
			while (tmp->type == 2)
				tmp = tmp->next;
			if (ft_is_dir(tmp) == 1)
			{
				if (last_dir->type == PIPE && tmp->type != PIPE)
					break ;
				// do not forget to use write(2) in every printf
				printf("mini-flemme: syntax error near unexpected token `%s'\n", tmp->lexeme);
				return (1);
			}
			else
				break ;
		}
		tmp = tmp->next;
	}
	if (last_verrif(tmp) == 1)
		return (1);
	return (0);
}
