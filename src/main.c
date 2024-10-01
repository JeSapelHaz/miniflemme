/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/10/01 14:16:06 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_quit(void)
{
	exit(0);
}

/////// TO DO : commencer a lancer des commandes simples pour commencer ? normalement avec notre pipex ca devrait aller vite
// pas oublier de bash --posix pour tester (je sais pas encore pourquoi)
int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*token_list;
	t_node	*root;

	(void)env; 
	check_args(ac, av);
	printf("belle bito\n"); // aucun interet mais drole ok 
	
	while (1)
	{
		str = readline("mini-flemme$ "); // nom du bash 
		if (!str || str[0] == '\0')
			break ;
		token_list = tokenize(str);
		printf("after tokenize\n"); 
		root = parse_command(&token_list); // ici petit probleme : si on met pas de '\n' a la fin boucle infini ou segfault
		print_node_tree(root, 0); // fonction qui visualise juste les nodes pour plus de clarté 
		printf("%s\n", get_path(str, env));
		char **cmd;
		cmd = ft_split(str, ' ');
		execve(get_path(cmd[0], env), cmd, env); // execute la commande mais ferme tout 
		ft_free_token(&token_list);
		add_history(str); // je suis tellement le goat de ce jeu 
		free(str);
	}
	clear_history();
	free(str);
	return (0);// a quoi sert le putain de return 0 je ne sais pas mais ca fait joli 
	// le return c'est parce que le main il veut un int et surtout on peut l'utiliser pour exit -1
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
