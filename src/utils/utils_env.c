/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:00:16 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/06 11:04:12 by hbutt            ###   ########.fr       */
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
	printf("on rentre dans le copy env -------------------------------------------------\n");
	env_size = get_2d_array_size(env);
	printf("on rentre dans le copy env ------------------------------------------------- taille : %ld\n", env_size);
	new_env = malloc(sizeof(char *) * (env_size + 1));
	printf("on rentre dans le copy env -------------------------------------------------\n");
	if (!new_env)
		return (NULL);
	printf("on rentre dans le copy env -------------------------------------------------\n");
	printf("%ld\n", i);
	while (i < env_size)
	{
		printf("%ld %s\n", i, env[i]);
		new_env[i] = ft_strdup(env[i]);
		printf("%ld %s\n", i, new_env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
