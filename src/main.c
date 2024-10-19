/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/10/19 15:03:59 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*token_list;
	t_node	*node;
	t_token	*tmp;

	(void)env; 
	check_args(ac, av);
	while (1)
	{
		str = readline("mini-flemme$ "); 
		if (!str || str[0] == '\0')
			break ;
		token_list = tokenize(str);
		tmp = last_token(token_list);
		tmp = tmp->prev;
		while (tmp->type == PIPE)
		{
			ft_last_pipe(token_list);
			tmp = last_token(token_list);
			tmp = tmp->prev;
		}
		node = parse(&token_list);
		print_node(node);
		print_token_list(token_list);
		ft_free_token(&token_list);
		add_history(str);  
		free(str);
	}
	clear_history();
	free(str);
	return (0);
}
