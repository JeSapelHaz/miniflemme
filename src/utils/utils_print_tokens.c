/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:15:07 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/06 15:56:32 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"


void	print_tokens(t_token *token_list)
{
	int i = 0;

	while(token_list)
	{
		printf("%d - Lexeme : %s\n", i, token_list->lexeme);
		i++;
		token_list = token_list->next;
	} 
}