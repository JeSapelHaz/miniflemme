/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:16 by hbutt             #+#    #+#             */
/*   Updated: 2024/12/22 15:43:27 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// static void	ft_sort_env(char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;

// 	if (!env || !env[0])
// 		return ;
// 	i = 0;
// 	while (env[i])
// 	{
// 		j = i + 1;
// 		while (env[j])
// 		{
// 			if (ft_strcmp(env[i], env[j]) > 0)
// 			{
// 				temp = env[i];
// 				env[i] = env[j];
// 				env[j] = temp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void	ft_print_env(char **env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (env[i])
// 	{
// 		write(1, "declare -x ", 11);
// 		j = 0;
// 		while (env[i][j] && env[i][j] != '=')
// 		{
// 			write(1, &env[i][j], 1);
// 			j++;
// 		}
// 		if (env[i][j] == '=')
// 		{
// 			write(1, "=\"", 2);
// 			j++;
// 			while (env[i][j])
// 				write(1, &env[i][j++], 1);
// 			write(1, "\"", 1);
// 		}
// 		write(1, "\n", 1);
// 		i++;
// 	}
// }
// static int	get_env_index(char **env, const char *arg)
// {
// 	int		i;
// 	size_t	len;

// 	len = 0;
// 	while (arg[len] && arg[len] != '=')
// 		len++;
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], arg, len) && env[i][len] == '=')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// static void	replace_env_value(char **env, const char *arg, int index)
// {
// 	free(env[index]);
// 	env[index] = ft_strdup(arg);
// }

// static void	add_new_env_variable(char ***env, const char *arg)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	while ((*env)[i])
// 		i++;
// 	new_env = malloc(sizeof(char *) * (i + 2));
// 	if (!new_env)
// 		return ;
// 	i = 0;
// 	while ((*env)[i])
// 	{
// 		new_env[i] = (*env)[i];
// 		i++;
// 	}
// 	new_env[i] = ft_strdup(arg);
// 	new_env[i + 1] = NULL;
// 	free(*env);
// 	*env = new_env;
// }

// static int	verify_export_name(const char *str)
// {
// 	int	i;

// 	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
// 		return (0);
// 	i = 1;
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static void	handle_export_error(const char *arg)
// {
// 	write(2, "export: `", 9);
// 	write(2, arg, ft_strlen(arg));
// 	write(2, "': not a valid identifier\n", 26);
// }
// void	free_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		free(env[i]);
// 		i++;
// 	}
// 	free(env);
// }

// void	ft_export(char **args, char ***env)
// {
// 	int		i;
// 	int		index;
// 	char	*temp;

// 	if (!args[1])
// 	{
// 		char **sorted_env = copy_env(*env);
// 		if (!sorted_env)
// 			return ;
// 		ft_sort_env(sorted_env);
// 		ft_print_env(sorted_env);
// 		free_env(sorted_env);
// 		return ;
// 	}
// 	i = 1;
// 	while (args[i])
// 	{
// 		if (!verify_export_name(args[i]))
// 		{
// 			handle_export_error(args[i]);
// 			excode = 1;
// 		}
// 		else
// 		{
// 			if (!ft_strchr(args[i], '='))
// 			{
// 				temp = ft_strjoin(args[i], "=");
// 				if (!temp)
// 					return ;
// 				index = get_env_index(*env, temp);
// 				if (index != -1)
// 					replace_env_value(*env, temp, index);
// 				else
// 					add_new_env_variable(env, temp);
// 				free(temp);
// 			}
// 			else
// 			{
// 				index = get_env_index(*env, args[i]);
// 				if (index != -1)
// 					replace_env_value(*env, args[i], index);
// 				else
// 					add_new_env_variable(env, args[i]);
// 			}
// 		}
// 		i++;
// 	}
// }
