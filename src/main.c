/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/09/28 16:21:56 by hbutt            ###   ########.fr       */
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

void	ft_quit(void)
{
	exit(0);
}

int	check_args(int ac, char **av)
{
	if (ac > 1)
		ft_quit();
	(void)av;
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char *str;

// 	char **cmd_gui = NULL;
// 	cmd_gui[0] = "ls";

// 	check_args(ac, av);
// 	printf("belle bito\n");
// 	while (1)
// 	{
// 		str = readline("mini-flemme$ ");
// 		printf("%s\n", str);
// 		if (!str || str[0] == '\0')
// 			break ;
// 		if (ft_strcmp(str, "ls") == 0)
// 			execve(get_path("ls", env), cmd_gui, env);
// 		add_history(str);
// 		free(str);
// 	}
// 	clear_history();
// 	free(str);
// 	return (0);
// }

int	main(void)
{
    t_token	*token_list;

    // Tokeniser une commande
    token_list = tokenize("echo Hello | grep minishell > output.txt");

    // Afficher les tokens
    t_token *current = token_list;
    while (current)
    {
        printf("Token: %s\n", current->lexeme);
        current = current->next;
    }

    // Libérer la mémoire allouée pour les tokens (à implémenter avec ft_free_token)
    ft_free_token(&token_list);

    return (0);
}
