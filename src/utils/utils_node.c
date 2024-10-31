/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:51:39 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/31 19:33:03 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_node	*left_before_pipe(t_node *left, t_token **token)
{
	t_node	*l;
	t_token	*tok;

	tok = (*token);
	printf("%s\n", tok->prev->lexeme);
	while (tok->prev != NULL && tok->type != PIPE)
		tok = tok->prev;
	printf("hello\n");
	l = str_node(&tok, 0);
	while (tok && (tok->type != PIPE && tok->type != END_TOKEN))
	{
		if (ft_is_dir(tok))
			l = pair_node(l, &tok);
		tok = tok->next;
	}
	free(left);
	printf("left %s")
	return (l);
}
