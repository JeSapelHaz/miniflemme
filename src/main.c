/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/11/23 17:03:27 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_token	*re_do_token(char **str)
{
	t_token	*token_list;

	*str = readline("mini-flemme$ ");
	if (!(*str) || (*str)[0] == '\0')
		return (NULL);
	token_list = tokenize(*str);
	if (!token_list)
		add_history(*str);
	return (token_list);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_token	*token_list;
	t_node	*node;
	t_token	*tmp;

	check_args(ac, av);
	str = NULL;
	token_list = NULL;
	while (1)
	{
		while (ft_verrif_tok(&token_list) == 1)
			token_list = re_do_token(&str);
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
		}
		add_history(str);
		if (ft_verrif_tok(&token_list) == 0)
		{
			print_token_list(token_list);
			node = parse(&token_list);
			print_node(node);
			ft_exe(node, envp);
		}
		ft_free_all_node(&node);
		ft_free_token(&token_list);
		free(str);
	}
	clear_history();
	free(str);
	return (0);
}
