/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/09/29 18:33:10 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_quit(void)
{
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*token_list;
	t_node	*root;

	(void)env;
	check_args(ac, av);
	printf("belle bito\n");
	while (1)
	{
		str = readline("mini-flemme$ ");
		if (!str || str[0] == '\0')
			break ;
		token_list = tokenize(str);
		root = parse_command(&token_list);
		print_node_tree(root, 0);
		ft_free_token(&token_list);
		add_history(str);
		free(str);
	}
	clear_history();
	free(str);
	return (0);
}

// int	main(void)
// {
// 	// current = token_list;
// 	// while (current->type != END_TOKEN)
// 	// {
// 	// 	printf("Token: %s\n", current->lexeme);
// 	// 	current = current->next;
// 	// }
// 	ft_free_token(&token_list);
// 	return (0);
// }
