/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:16 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/29 17:03:07 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_print_var(char *var)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (var[i] && var[i] != '=')
	{
		printf("%c", var[i]);
		i++;
	}
	if (var[i] == '=')
	{
		printf("=\"");
		i++;
		while (var[i])
		{
			printf("%c", var[i]);
			i++;
		}
		printf("\"");
	}
	printf("\n");
}

static void	ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_add_to_env(char ***env, char *arg)
{
	int		i;
	char	**env_temp;

	(void)arg;
	(void)env;
	env_temp = *env;
	i = 0;
	while ((env_temp[i]))
		i++;
	env_temp[i] = ft_strdup(arg);
	env_temp[i + 1] = NULL;
}

void	ft_export(char **args, char ***env)
{
	size_t	i;
	char	**new_env;

	i = 0;
	(void)args;
	new_env = *env;
	if (!new_env)
		return ;
	if (!args[1])
	{
		ft_sort_env(new_env);
		while (new_env[i])
		{
			ft_print_var(new_env[i]);
			i++;
		}
		return ;
	}
	i = 1;
	while (args[i])
	{
		ft_add_to_env(env, args[i]);
		i++;
	}
}
