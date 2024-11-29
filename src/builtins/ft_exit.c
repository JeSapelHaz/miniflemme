/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:19:12 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/29 15:00:38 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	is_numeric(const char *str)
{
	int i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char *args)
{
	int exit_code;

	printf("exit\n"); 

	if (!args)
		exit(0);

	if (!is_numeric(args)) 
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args);
		exit(255);
	}

	exit_code = atoi(args);

	
    
	exit(exit_code);
}