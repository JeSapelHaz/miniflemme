/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/11/26 14:39:09 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_token	*re_do_token(char **str)
{
	t_token	*token_list;

	if (str || *str)
		add_history(*str);
	*str = readline("mini-flemme$ ");
	if (!(*str) || (*str)[0] == '\0')
		return (NULL);
	token_list = tokenize(*str);
	return (token_list);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_token	*token_list;
	t_node	*node;
	t_token	*tmp;
	int	end[2];
	int	added;

	added = 0;
	check_args(ac, av);
	while (1)
	{
		token_list = NULL;
		str = NULL;
		while (ft_verrif_tok(&token_list) == 1)
		{
			ft_free_token(&token_list);
			free(str);
			token_list = re_do_token(&str);
			add_history(str);
			added  = 1;
		}
		tmp = last_token(token_list);
		if (tmp->prev)
			tmp = tmp->prev;
		while (tmp->type == SPACE_TOKEN && tmp->prev != END_TOKEN)
			tmp = tmp->prev;
		while (tmp->type == PIPE)
		{
			str = ft_last_pipe(&token_list, str);
			tmp = last_token(token_list);
			tmp = tmp->prev;
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
//			print_node(node);
			ft_exe(node, envp, end);
		}
		ft_free_all_node(&node);
		ft_free_token(&token_list);
		free(str);
	}
	clear_history();
	free(str);
	return (0);
}
