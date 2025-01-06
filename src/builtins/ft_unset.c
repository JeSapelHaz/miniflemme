/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:21 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/06 12:11:47 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static size_t	get_2d_array_size(char **array)
{
	size_t	size;

	size = 0;
	while (array && array[size])
		size++;
	return (size);
}

void	ft_unset(char **args, char ***env)
{
	char	**new_env;
	int		i;
	int		j;
	int		k;
	size_t	env_size;

	if (!args || !args[1])
		return ;
	new_env = *env;
	env_size = get_2d_array_size(new_env);
	i = 0;
	while (i < (int)env_size)
	{
		j = 1;
		while (args[j])
		{
			if ((strncmp(new_env[i], args[j], strlen(args[j])) == 0
					&& new_env[i][strlen(args[j])] == '\0')
				|| (strncmp(new_env[i], args[j], strlen(args[j])) == 0
					&& new_env[i][strlen(args[j])] == '='))
			{
				free(new_env[i]);
				k = i;
				while (k < (int)(env_size - 1))
				{
					new_env[k] = new_env[k + 1];
					k++;
				}
				new_env[k] = NULL;
				env_size--;
				i--;
				break ;
			}
			j++;
		}
		i++;
	}
}
