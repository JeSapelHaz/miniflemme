/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:53:38 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/04 16:57:28 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void parser(t_token **token_list)
{
	char **list_cmd;
	int i;

	i = 0;
	while(token_list[i])
	{
		if ((*token_list)->type == PIPE)
	}
}
