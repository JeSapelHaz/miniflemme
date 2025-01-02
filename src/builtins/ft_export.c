/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:16 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/02 16:56:29 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_print_var(char *var)
{
	int	i;

	if (!var)
		return ;
	i = 0;
	write(1, "declare -x ", 11);
	while (var[i] && var[i] != '=')
	{
		write(1, &var[i], 1);
		i++;
	}
	if (var[i] == '=')
	{
		write(1, "=\"", 2);
		i++;
		while (var[i])
		{
			write(1, &var[i], 1);
			i++;
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
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
	char	**new_env;

	env_temp = *env;
	i = 0;
	while (env_temp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	for (i = 0; env_temp[i]; i++)
		new_env[i] = env_temp[i];
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	free(env_temp);
	*env = new_env;
}

int	verify_export_name(const char *str)
{
	int	i;

	if (!str || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	write_error(const char *name)
{
	write(2, "export: `", 9);
	write(2, name, ft_strlen(name));
	write(2, "': not a valid identifier\n", 26);
}

void	ft_export(char **args, char ***env)
{
	size_t	i;
	char	**current_env;

	i = 0;
	current_env = *env;
	if (!current_env)
		return ;
	if (!args[1])
	{
		ft_sort_env(current_env);
		while (current_env[i])
		{
			ft_print_var(current_env[i]);
			i++;
		}
		return ;
	}
	for (i = 1; args[i]; i++)
	{
		if (!verify_export_name(args[i]))
		{
			write_error(args[i]);
			excode = 1;
		}
		else
		{
			ft_add_to_env(env, args[i]);
		}
	}
}
