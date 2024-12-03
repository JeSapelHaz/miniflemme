/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:26:50 by alama             #+#    #+#             */
/*   Updated: 2024/12/03 16:04:52 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	add_space_split(char **data)
{
	int	i;
	int	j;
	char	*str;

	j = 0;
	while (data[j] != NULL)
	{
		str = data[j];
		i = 0;
		while (str[i])
		{
			if (str[i] == -32)
				str[i] *= -1;
			i++;
		}
		j++;
	}
}

void	split_for_exe(t_node *node)
{
	int	i;
	char	*str;

	i = 0;
	str = node->data.str;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i + 1] && str[i + 1] != '\'' && str[i] != '\\')
			{
				if (str[i] == ' ')
					str[i] = str[i] *-1;
				i++;
			}
		}
		if (str[i] == '\"')
		{
			while (str[i + 1] && str[i + 1] != '\"' && str[i] != '\\')
			{
				if (str[i] == ' ')
					str[i] = str[i] *-1;
				i++;
			}
		}
		i++;
	}
}

void	remove_quote(char **data)
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] && data[i][j + 1] == '\''
				&& data[i][j] != '\\')
			{
				str = ft_strtrim(data[i], "\'");
				free(data[i]);
				data[i] = str;
				break ;
			}
			if (data[i][j] && data[i][j + 1] == '\"'
				&& data[i][j] != '\\')
			{
				str = ft_strtrim(data[i], "\"");
				free(data[i]);
				data[i] = str;
				break ;
			}
			j++;
		}
		i++;
	}
}
