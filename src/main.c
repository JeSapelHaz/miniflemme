/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/09/28 18:10:16 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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
	t_token	*current;

	token_list = tokenize("ceci est un test | test2 grep < > ok\n");
	current = token_list;
	while (current->type != END_TOKEN)
	{
		printf("Token: %s\n", current->lexeme);
		current = current->next;
	}
	ft_free_token(&token_list);
	return (0);
}
