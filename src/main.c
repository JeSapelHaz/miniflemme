/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2025/01/14 16:21:39 by alama            ###   ########.fr       */
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

static	t_all	*set_all(void)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->boucle = 1;
	return (all);
}

int	main(int ac, char **av, char **envp)
{
	char	**env;
	t_token	*tmp;
	t_all	*all;
	int		added;

	g_excode = 0;
	check_args(ac, av);
	env = copy_env(envp);
	all = set_all();
	while (all->boucle != -1)
	{
		initialize_signals();
		all->token_list = NULL;
		all->str = NULL;
		while (ft_verrif_tok(&all->token_list) != 0)
		{
			ft_free_token(&all->token_list);
			free(all->str);
			all->str = NULL;
			all->token_list = NULL;
			all->token_list = re_do_token(&all->str);
			added = 1;
		}
		tmp = find_pipe(all->token_list);
		while (tmp->type == PIPE)
		{
			all->str = ft_last_pipe(&all->token_list, all->str);
			tmp = last_token(all->token_list)->prev;
			while (tmp->type == SPACE_TOKEN)
				tmp = tmp->prev;
			added = 0;
		}
		if (added == 0)
			add_history(all->str);
		if (ft_verrif_tok(&all->token_list) == 0)
		{
			all->node = parse(&all->token_list);
			add_dollar(all->node, env);
			clean_str_nodes(all->node);
			all->boucle = ft_exe(all->node, env);
		}
		ft_free_all_node(&all->node);
		ft_free_token(&all->token_list);
		free(all->str);
	}
	free(all);
	clear_history();
	return (g_excode);
}
