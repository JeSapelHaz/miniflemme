/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:51:39 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/30 21:42:11 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_node	*left_before_pipe(t_node *left, t_token **token)
{
	t_node	*l;

	tok = *token;
	while (tok->prev || tok->type != PIPE)
		tok = tok->prev;
	l = str_node(&tok, 0);
	while (tok && (tok->type != PIPE || tok->type != END_TOKEN))
	{
		if (ft_is_dir(l))
			l = pair_node(l, &tok);
		tok = tok->next;
	}
	//free(left);
	return (l);
}
