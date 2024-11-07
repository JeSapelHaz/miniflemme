/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/11/05 14:16:34 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	cwd[1024];
	char	*current_dir;

	check_args(ac, av);
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			current_dir = ft_strrchr(cwd, '/'); // Trouve le dernier '/'
			if (current_dir && *(current_dir + 1) != '\0')
			{
				printf("%s$ ", current_dir + 1);
					// Affiche seulement le dossier courant
			}
			else
			{
				printf("mini-flemme$ ");
			}
		}
		else
		{
			perror("getcwd() error");
			return (1);
		}
		str = readline("");
		if (ft_strncmp(str, "exit", 4) == 0)
			ft_exit(str);
		if (ft_strncmp(str, "echo", 4) == 0)
			ft_echo(str);
		if (ft_strncmp(str, "cd", 2) == 0)
			ft_cd(str);
		if (ft_strncmp(str, "pwd", 3) == 0)
			ft_pwd();
		if (ft_strncmp(str, "env", 3) == 0)
			ft_env(str, env);
		add_history(str);
	}
}

// t_token	*re_do_token(char *str)
// {
// 	t_token	*token_list;

// 	str = readline("mini-flemme$ ");
// 	if (!str || str[0] == '\0')
// 		return (NULL);
// 	if (ft_strcmp(str, "exit") == 0)
// 		ft_exit(str);
// 	if (ft_strncmp(str, "echo", 4) == 0)
// 		ft_echo(str);
// 	token_list = tokenize(str);
// 	add_history(str);
// 	return (token_list);
// }

// int	main(int ac, char **av, char **env)
// {
// 	char	*str;
// 	t_token	*token_list;
// 	t_node	*node;
// 	t_token	*tmp;

// 	(void)env;
// 	check_args(ac, av);
// 	str = NULL;
// 	token_list = NULL;
// 	while (1)
// 	{
// 		while (ft_verrif_tok(&token_list) == 1)
// 			token_list = re_do_token(str);
// 		tmp = last_token(token_list);
// 		tmp = tmp->prev;
// 		while (tmp->type == SPACE_TOKEN)
// 				tmp = tmp->prev;
// 		while (tmp->type == PIPE)
// 		{
// 			ft_last_pipe(&token_list);
// 			tmp = last_token(token_list);
// 			tmp = tmp->prev;
// 			while (tmp->type == SPACE_TOKEN)
// 				tmp = tmp->prev;
// 		}
// 		if (ft_verrif_tok(&token_list) == 0)
// 		{
// 			// print_token_list(token_list);
// 			node = parse(&token_list);
// 			//print_node(node);
// 			(void)node;
// 		}
// 		ft_free_token(&token_list);
// 	}
// 	clear_history();
// 	free(str);
// 	return (0);
// }
