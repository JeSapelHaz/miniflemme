/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verrif_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:50:36 by alama             #+#    #+#             */
/*   Updated: 2024/10/19 18:48:01 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_verrif_tok(t_token **token_list, char *str)
{
	t_token	*tmp;

	if (!token_list || !*token_list)
		return (1);
	tmp = last_token(*token_list);
	tmp = tmp->prev;
	if (tmp->type == O_DIR || tmp->type == OA_DIR || tmp->type == DI_DIR
			|| tmp->type == I_DIR)
	{
		printf("syntax error near unexpected token `newline'\n");
		free(str);
		ft_free_token(token_list);
		return (1);
	}
	/*
	while (tmp->next->type != END_TOKEN)
	{
		if (tmp->type == PIPE || tmp->type == O_DIR || I)
	}
	*/
	return (0);
}
