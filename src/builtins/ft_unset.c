/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:21 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/02 16:56:32 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_unset(char **args, char ***env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	new_env = *env;
	while (new_env[i])
	{
		j = 1;
		while (args[j])
		{
			if (ft_strncmp(new_env[i], args[j], ft_strlen(args[j])) == 0
				&& new_env[i][ft_strlen(args[j])] == '\0')
			{
				new_env[i] = NULL;
				break ;
			}
			if (ft_strncmp(new_env[i], args[j], ft_strlen(args[j])) == 0
				&& new_env[i][ft_strlen(args[j])] == '=')
			{
				new_env[i] = NULL;
				break ;
			}
			j++;
		}
		i++;
	}
}
