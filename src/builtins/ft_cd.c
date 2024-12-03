/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:07 by hbutt             #+#    #+#             */
/*   Updated: 2024/12/03 16:34:02 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_cd(char **args)
{
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME"); 
		if (!home)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return ;
		}
		if (chdir(home) == -1)
			perror("minishell: cd");
	}
	else if (chdir(args[1]) != 0)
		perror("minishell: cd");
}
