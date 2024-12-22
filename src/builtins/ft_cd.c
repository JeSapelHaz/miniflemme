/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:07 by hbutt             #+#    #+#             */
/*   Updated: 2024/12/20 17:22:04 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_cd(char **args)
{
	char	*home;
	char	*error_msg;

	if (args[2])
	{
		excode = 1;
		write(2, " too many arguments\n", 14);
		return ;
	}
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		home = getenv("HOME");
		if (!home)
		{
			error_msg = "minishell: cd: HOME not set\n";
			write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
			excode = 0;
			return ;
		}
		if (chdir(home) == -1)
		{
			perror("minishell: cd");
			excode = 1;
		}
	}
	else if (chdir(args[1]) == -1)
	{
		perror("minishell: cd");
		excode = 1;
	}
	else
		excode = 0;
}
