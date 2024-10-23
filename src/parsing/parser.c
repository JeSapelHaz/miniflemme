/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:37:20 by alama             #+#    #+#             */
/*   Updated: 2024/10/23 16:14:39 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_node	*parse(t_token **token_list)
{
	t_node	*node;
	t_token	*token;

	token = (*token_list);
	while (token->type != END_TOKEN)
	{
		if (ft_is_dir(token) == 1)
		{


		}
	}
}
