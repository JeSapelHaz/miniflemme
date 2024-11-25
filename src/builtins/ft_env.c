/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:12 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/25 17:10:29 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_env(char **args, char **env)
{
	int i;

	i = 0;
	(void) args;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	
}