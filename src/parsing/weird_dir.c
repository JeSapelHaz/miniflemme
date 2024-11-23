/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:03:43 by alama             #+#    #+#             */
/*   Updated: 2024/11/23 19:18:52 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	set_left_arg(t_token **token, t_node *left)
{
	char	*tmp;

	if (left->type == STR_NODE)
	{
		while (ft_is_dir(*token) == 0 && (*token)->type != END_TOKEN)
		{
			tmp = ft_strjoin(left->data.str, (*token)->lexeme);
			free(left->data.str);
			left->data.str = ft_strdup(tmp);
			*token = (*token)->next;
			free(tmp);
		}
	}
	printf("here : %s\n", left->data.str);
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

void	set_right_space(t_node *left, t_node *right)
{
	char	**str;
	int		i;
	char	*tmp;
	char	*space;

	str = ft_split(right->data.str, ' ');
	i = 1;
	while (str[i] != NULL)
	{
		space = ft_strjoin(left->data.str, " ");
		tmp = ft_strjoin(space, str[i]);
		free(space);
		free(left->data.str);
		left->data.str = tmp;
		i++;
	}
	if (str[1] != NULL)
	{
		free(right->data.str);
		right->data.str = ft_strdup(str[0]);
	}
	ft_free_str(str);
}
