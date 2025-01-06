/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:16 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/06 11:07:01 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_export(char **args, char ***env)
{
	int		i;
	char	*var;
	char	*equal_pos;
	int		j;
	int		exists;
	int		len;
	char	**new_env;

	i = 1;
	if (!args[1])
	{
		while (*env && (*env)[i] != NULL)
		{
		    printf("declare -x %s\n", (*env)[i]);
			i++;
		}
		return ;
	}
	while (args[i] != NULL)
	{
		var = args[i];
		equal_pos = ft_strchr(var, '=');
		if (equal_pos && equal_pos != var) 
		{
			exists = 0;
			j = 0;
			while ((*env)[j] != NULL)
			{
				if (ft_strncmp((*env)[j], var, equal_pos - var) == 0 &&
					(*env)[j][equal_pos - var] == '=')
				{
					exists = 1;
					break ;
				}
				j++;
			}
			if (!exists)
			{
				len = 0;
				while ((*env)[len] != NULL)
					len++;
				new_env = (char **)malloc(sizeof(char *) * (len + 2));
				if (!new_env)
					exit(1);
				j = 0;
				while (j < len)
				{
					new_env[j] = (*env)[j];
					j++;
				}
				new_env[j] = ft_strdup(var);
				new_env[j + 1] = NULL;
				free(*env);
				*env = new_env;
			}
		}
		else
			write(2, "export: invalid identifier\n", 27);
		i++;
	}
}
