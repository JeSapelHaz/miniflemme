/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/10/01 18:15:27 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"


int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*token_list;
	t_node	*root;

	(void)env; 
	check_args(ac, av);
	printf("belle bito\n"); 
	
	// signal(SIGINT, handle_signal);
	while (1)
	{
		str = readline("mini-flemme$ "); 
		if (!str || str[0] == '\0')
			break ;
		token_list = tokenize(str);
		root = parse_command(&token_list); 
		print_node_tree(root, 0);  
		printf("%s\n", get_path(str, env));
		printf("\n");
		char **cmd;
		cmd = ft_split(str, ' ');
		execve(get_path(cmd[0], env), cmd, env); // execute la commande mais ferme tout 
		ft_free_token(&token_list);
		add_history(str);  
		free(str);
	}
	clear_history();
	free(str);
	return (0);
}