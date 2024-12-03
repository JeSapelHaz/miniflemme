/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:06:11 by alama             #+#    #+#             */
/*   Updated: 2024/11/28 13:18:59 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*new_pipe(t_token **t, char **str, t_token **token_list)
{
	t_token	*tmp;
	char	*new_rd;
	t_token	*new_token;
	char	*new;

	tmp = *t;
	new_rd = readline("> ");
	new_token = tokenize(new_rd);
	if (!new_token)
		return (free(*str),free(new_rd), NULL);
	while (tmp->next->type != END_TOKEN)
		tmp = tmp->next;
	remove_end(token_list);
	ft_add_next(tmp, token_list, new_token);
	new = ft_strjoin(*str, new_rd);
	free(*str);
	*str = NULL;
	free(new_rd);
	new_rd = NULL;
	return (new);
}

t_token	*find_pipe(t_token *token_list)
{
	t_token	*tmp;

	if (token_list == NULL)
		return (NULL);
	tmp = last_token(token_list);
	if (tmp->prev)
		tmp = tmp->prev;
	while (tmp->type == SPACE_TOKEN && tmp->prev != END_TOKEN)
		tmp = tmp->prev;
	return (tmp);
}

char	*ft_last_pipe(t_token **token_list, char *str)
{
	t_token	*tmp;

	tmp = *token_list;
	tmp = last_token(*token_list);
	tmp = tmp->prev;
	while (tmp->type == SPACE_TOKEN)
		tmp = tmp->prev;
	if (tmp->type == PIPE)
		return (new_pipe(&tmp, &str, token_list));
	return (NULL);
}
