/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:19:12 by hbutt             #+#    #+#             */
/*   Updated: 2024/12/12 16:03:08 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
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

void	ft_exit(char **args)
{
	write(1, "exit\n", 5);
	if (args[1] == NULL)
		exit(0);
	if (!is_numeric(args[1]))
	{
		// utilise write pas fprintf car interdit
		//fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
		//	args);
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	if (args[2] != NULL)
	{
		write(2, "minishell: exit: ", 17);
		write(2, "too many argument\n", 18);
		excode = 1;
		return ;
	}
	excode = atoi(args[1]);
	exit(excode);
}
