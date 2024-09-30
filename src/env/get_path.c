/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:45:28 by hbutt             #+#    #+#             */
/*   Updated: 2024/09/30 14:49:21 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	ft_compare_path(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static char	*ft_getenv(char *name, char **env)
{
	int		i;
	char	*name_path;

	i = 0;
	while (env[i])
	{
		name_path = ft_substr(env[i], 0, 4);
		if (ft_compare_path(name_path, name) == 0)
		{
			free(name_path);
			return (env[i] + 5);
		}
		free(name_path);
		i++;
	}
	return (0);
}
void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}


char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*good_exec;
	char	**path_split;
	char	*tmp;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path_split = ft_split(ft_getenv("PATH", env), ':');
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		good_exec = ft_strjoin(tmp, cmd);
		if (access(good_exec, X_OK) == 0)
		{
			ft_free_tab(path_split);
			free(tmp);
			return (good_exec);
		}
		free(good_exec);
		free(tmp);
		i++;
	}
	ft_free_tab(path_split);
	return (cmd);
}
