/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:03:43 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 16:26:11 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	set_right_space(t_node *left, t_node *right)
{
	char	**str;
	int	i;
	char	*tmp;
	char	*space;
	t_node	*l;

	l = left;
	str = ft_split_quote(right->data.str);
	if (!str)
		return ;
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
