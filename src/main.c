/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2025/01/08 15:44:13 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <signal.h>

int		g_excode = 0;

t_token	*re_do_token(char **str)
{
	t_token	*token_list;
	t_token	*tmp;

	*str = readline("mini-flemme$ ");
	if (!(*str))
		return (ft_exit(NULL), NULL);
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
	int		added;

	g_excode = 0;
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
			node = parse(&token_list);
			// print_node(node);
			add_dollar(node, env);
			clean_str_nodes(node);
			ft_exe(node, env);
		}
		ft_free_all_node(&node);
		ft_free_token(&token_list);
		free(str);
	}
	clear_history();
	free(str);
	return (g_excode);
}
