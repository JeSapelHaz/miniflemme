/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:03:43 by alama             #+#    #+#             */
/*   Updated: 2024/12/04 14:44:34 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

/*
static void	set_left_arg(t_token **token, t_node *left)
{
	char	*tmp;
	t_node	*tmp_node;

	tmp_node = left;
	while (tmp_node->type == PAIR_NODE)
		tmp_node = tmp_node->data.pair.left;
	if (tmp_node->type == STR_NODE)
	{
		while (ft_is_dir(*token) == 0 && (*token)->type != END_TOKEN)
		{
			tmp = ft_strjoin(tmp_node->data.str, (*token)->lexeme);
			free(tmp_node->data.str);
			tmp_node->data.str = ft_strdup(tmp);
			*token = (*token)->next;
			free(tmp);
		}
	}
	if ((*token)->type == END_TOKEN)
		*token = (*token)->prev;
}

t_node	*set_right_file(t_token **token, t_node *left)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!token || (*token)->type == END_TOKEN || ft_is_dir(*token) == 1)
		return (NULL);
	if (!node)
		return (NULL);
	node->type = STR_NODE;
	while ((*token)->type == SPACE_TOKEN)
		*token = (*token)->next;
	node->data.str = ft_strdup((*token)->lexeme);
	*token = (*token)->next;
	while ((*token)->type == SPACE_TOKEN)
		*token = (*token)->next;
	set_left_arg(token, left);
	return (node);
}
*/

void	set_right_space(t_node *left, t_node *right)
{
	char	**str;
	int		i;
	char	*tmp;
	char	*space;
	t_node	*l;

	l = left;
	str = ft_split(right->data.str, ' ');
	i = 1;
	while (str[i] != NULL)
	{
		while (l->type != STR_NODE)
			l = l->data.pair.left;
		space = ft_strjoin(l->data.str, " ");
		tmp = ft_strjoin(space, str[i]);
		free(space);
		free(l->data.str);
		l->data.str = tmp;
		i++;
	}
	free(right->data.str);
	right->data.str = ft_strdup(str[0]);
	ft_free_str(str);
}
