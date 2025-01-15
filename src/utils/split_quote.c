/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:23:06 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 15:02:32 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	ft_handle_quote(char const *str, int i)
{
	int	j;

	j = 1;
	i++;
	if (str[i - 1] == '\'')
	{
		while (str[i] && str[i] != '\'')
		{
			j++;
			i++;
		}
		return (j + 1);
	}
	while (str[i] && str[i] != '\"')
	{
		j++;
		i++;
	}
	return (j + 1);
}

static int	ft_count_split(char const *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\"' || str[i] == '\'')
				i += ft_handle_quote(str, i);
			else
			{
				while (str[i] && str[i] != '\'' && str[i] != '\"'
					&& str[i] != ' ')
					i++;
			}
		}
		if (str[i] == ' ')
			i++;
		count++;
	}
	return (count);
}

static void	ft_add_str(char ***split, char const *str)
{
	int	i;
	int	nb;
	int	l;

	nb = 0;
	i = 0;
	while (str[i])
	{
		l = 0;
		while (str[i + l] && str[i + l] != ' ')
		{
			if (str[i + l] == '\"' || str[i + l] == '\'')
				l += ft_handle_quote(str, i + l);
			else
			{
				while (str[i + l] && str[i + l] != '\'' && str[i + l] != '\"'
					&& str[i + l] != ' ')
					l++;
			}
		}
		(*split)[nb] = ft_substr(str, i, l);
		nb++;
		i += l;
		if (str[i] == ' ')
			i++;
	}
}

char	**ft_split_quote(char const *str)
{
	char	**split;
	int		count;

	count = ft_count_split(str);
	if (count <= 1)
		return (NULL);
	split = malloc(sizeof(char *) * (count + 1));
	split[count] = NULL;
	ft_add_str(&split, str);
	return (split);
}
