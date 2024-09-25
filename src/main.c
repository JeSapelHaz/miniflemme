/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/09/25 15:42:46 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void ft_quit()
{
	exit(0);
}

int check_args(int ac, char **av)
{
	if (ac > 1)
		ft_quit();
	(void) av;
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	check_args();
	printf("belle bito\n");
	while (1)
	{
		str = readline("mini-flemme$ ");
		printf("%s\n", str);
		if (!str || str[0] == '\0')
			break ;
		// if (ft_strcmp(str, "ls") == 0)
			// exec(ls, env, )
		add_history(str);
		free(str);
	}
	clear_history();
	free(str);
	return (0);
}