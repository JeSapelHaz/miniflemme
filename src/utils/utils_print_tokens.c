/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:15:07 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/06 14:22:30 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"


void	print_token_list(t_token *token_list)
{
	if (!token_list)
		return ;
	int i = 1;
	t_token *current = token_list;
	do
	{
		printf("%i - Type : %u | Lexeme: %s\n", i, current->type, current->lexeme);
		current = current->next;
		i++;
	} while (current != token_list);
}