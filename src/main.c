/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/12/11 16:57:56 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <signal.h>

void	exit_or_not(t_token **token_list)
{
	while ((*token_list))
	{
		if (ft_strcmp((*token_list)->lexeme, "exit") == 0)
		{
			if ((*token_list)->next->next)
				ft_exit((*token_list)->next->next->lexeme);
			ft_exit("1");
		}
		if ((*token_list)->next->type == END_TOKEN)
			return ;
		*token_list = (*token_list)->next;
	}
}

t_token	*re_do_token(char **str)
{
	t_token	*token_list;
	t_token	*verify_exit;
	t_token	*tmp;

	*str = readline("mini-flemme$ ");
	if (!(*str))
		return (ft_exit(0), NULL);
	token_list = tokenize(*str);
	tmp = find_pipe(token_list);
	if (!tmp || tmp->type != PIPE)
		add_history(*str);
	verify_exit = tokenize(*str);
	exit_or_not(&verify_exit);
	return (token_list);
}

int	main(int ac, char **av, char **envp)
{
	t_token	*token_list;
	t_node	*node;
	char	**env;
	char	*str;
	t_token	*tmp;
	int		end[2];
	int		added;

	excode = 0;
	check_args(ac, av);
	env = copy_env(envp);
	while (1)
	{
		initialize_signals();
		token_list = NULL;
		str = NULL;
		while (ft_verrif_tok(&token_list) == 1)
		{
			ft_free_token(&token_list);
			free(str);
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
//			print_token_list(token_list);
			node = parse(&token_list);
//			add_dollar(node, env);
//			print_node(node); // Pour afficher l'arbre de parsing
			ft_exe(node, env, end);
		}
		ft_free_all_node(&node);
		ft_free_token(&token_list);
		free(str);
		printf("echo : %d\n", excode);
	}
	clear_history();
	free(str);
	return (excode);
}
