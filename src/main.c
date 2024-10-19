/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/10/19 18:47:40 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_token	*re_do_token(char *str)
{
	t_token	*token_list;

	str = readline("mini-flemme$ "); 
	if (!str || str[0] == '\0')
		return (NULL);
	token_list = tokenize(str);
	return (token_list);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*token_list;
	t_node	*node;
	t_token	*tmp;

	(void)env; 
	check_args(ac, av);
	str = NULL;
	token_list = NULL;
	while (1)
	{
		while (!token_list && ft_verrif_tok(&token_list, str) == 1) 
			token_list = re_do_token(str);
		tmp = last_token(token_list);
		tmp = tmp->prev;
		while (tmp->type == PIPE)
		{
			ft_last_pipe(token_list);
			while (!token_list && ft_verrif_tok(&token_list, str) == 1) 
				token_list = re_do_token(str);
			tmp = last_token(token_list);
			tmp = tmp->prev;
		}
		node = parse(&token_list);
		print_node(node);
		print_token_list(token_list);
		ft_free_token(&token_list);
		add_history(str);  
	}
	clear_history();
	free(str);
	return (0);
}
