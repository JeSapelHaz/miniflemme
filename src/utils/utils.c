/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:13:53 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/02 17:08:38 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	only_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	ft_quit(void)
{
	exit(0);
}

char	*trim_file(t_node *node)
{
	char	*str;
	int	last;

	str = NULL;
	if (node->type != STR_NODE)
		return (NULL);
	last = ft_strlen(node->data.str);
	if (node->data.str[0] == '\"' && node->data.str[last] == '\"')
		str = ft_strtrim(node->data.str, "\"");
	else if (node->data.str[0] == '\'' && node->data.str[last] == '\'')
		str = ft_strtrim(node->data.str, "\'");
	else
		str = ft_strdup(node->data.str);
	return (str);
}
