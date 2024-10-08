/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:15:07 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/07 20:35:49 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"


void	print_token_list(t_token *token_list)
{
	if (!token_list)
		return ;
	int i = 1;
	t_token *current = token_list;
	while (current != NULL)
	{
		if (current->type == 0)
			printf("%i - Type : %u | Lexeme: end\n", i, current->type);
		else
			printf("%i - Type : %u | Lexeme: %s\n", i, current->type, current->lexeme);
		current = current->next;
		i++;
	}
}
