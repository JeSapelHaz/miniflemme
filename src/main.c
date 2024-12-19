/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/12/17 15:42:04 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <signal.h>

int	excode = 0;



t_token	*re_do_token(char **str)
{
	t_token	*token_list;
	t_token	*tmp;

	*str = readline("mini-flemme$ ");
//	if (!(*str))
//	{
//		printf("coucou ah oui make sanse\n");
//		return (ft_exit(0), NULL);
//	}
	token_list = tokenize(*str);
	tmp = find_pipe(token_list);
	if (!tmp || tmp->type != PIPE)
		add_history(*str);
	return (token_list);
}

int	main(int ac, char **av, char **envp)
{
	t_token	*token_list;
	t_node	*node;
	char	**env;
	char	*str;
	t_token	*tmp;
	int	end[2];
	int	added;

	check_args(ac, av);
	env = copy_env(envp);
	while (1)
	{
		initialize_signals();
		token_list = NULL;
		str = NULL;
		while (ft_verrif_tok(&token_list) != 0)
		{
			ft_free_token(&token_list);
			free(str);
			str = NULL;
			token_list = NULL;
			token_list = re_do_token(&str);
			added = 1;
			excode = 258;
		}
		tmp = find_pipe(token_list);
		while (tmp->type == PIPE)
		{
			str = ft_last_pipe(&token_list, str);
			tmp = last_token(token_list)->prev;
			while (tmp->type == SPACE_TOKEN)
				tmp = tmp->prev;
			added = 0;
		}
		if (added == 0)
			add_history(str);
		if (ft_verrif_tok(&token_list) == 0)
		{
//			print_token_list(token_list);
			node = parse(&token_list);
			
			add_dollar(node, env);
			clean_str_nodes(node);
//			print_node(node); // Pour afficher l'arbre de parsing

			ft_exe(node, env, end);
		}
		ft_free_all_node(&node);
		ft_free_token(&token_list);
		free(str);
		printf("exit status : %d\n", excode);
	}
	clear_history();
	free(str);
	return (excode);
}
