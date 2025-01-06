/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:00:16 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/06 10:35:11 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static size_t	get_2d_array_size(char **array)
{
	size_t	size;

	size = 0;
	while (array && array[size])
		size++;
	return (size);
}

char	**copy_env(char **env)
{
	size_t	i;
	size_t	env_size;
	char	**new_env;

	i = 0;
	printf("ok1\n");
	env_size = get_2d_array_size(env);
	printf("ok2\n");
	new_env = malloc(sizeof(char *) * (1000));
	if (!new_env)
		return (NULL);
	printf("ok3\n");
	while (i < env_size)
	{
		printf("ok4\n");
		new_env[i] = ft_strdup(env[i]);
		printf("ok4bis\n");
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	printf("ok5\n");
	new_env[i] = NULL;
	return (new_env);
}
