/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/10/06 15:50:51 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	print_tokens(t_token *token_list)
{
	t_token	*current;
	int i = 1;

	current = token_list;
	do
	{
		printf("%d - Lexeme : %s\n", i, current->lexeme);
		current = current->next;
		i++;
	} while (current != token_list);
}
int	main(int ac, char **av, char **env)
{
	char *str;
	t_token *token_list;
	t_node *root = NULL;

	(void)env;
	check_args(ac, av);
	while (1)
	{
		str = readline("mini-flemme$ ");
		if (!str || str[0] == '\0')
			break ;
		token_list = tokenize(str);
		print_token_list(token_list);
		// root = parse(&token_list); 
		// printf("%s\n", get_path(str, env));
		// printf("\n");
		// char **cmd;
		// cmd = ft_split(str, ' ');
		// execve(get_path(cmd[0], env), cmd, env); // execute la commande mais ferme tout 
		ft_free_token(&token_list);
		add_history(str);
		free(str);
	}
	clear_history();
	free(str);
	return (0);
}