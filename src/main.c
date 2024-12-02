/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/11/29 17:23:41 by hbutt            ###   ########.fr       */
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
		if((*token_list)->next->type == END_TOKEN)
			return;
		*token_list = (*token_list)->next;
	}
}

t_token	*re_do_token(char **str)
{
	t_token	*token_list;
	t_token *verify_exit; 
	
	
	*str = readline("mini-flemme$ ");
	if (!(*str) || (*str)[0] == '\0')
		return (printf("exit\n"), NULL);
	token_list = tokenize(*str);
	verify_exit = tokenize(*str);
	exit_or_not(&verify_exit);
	if (!token_list)
		add_history(*str);
	return (token_list);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_token	*token_list;
	t_node	*node;
	// t_token	*tmp;
	char	**env;
	
	
	
	env = copy_env(envp);
	check_args(ac, av);
	str = NULL;
	token_list = NULL;
	while (1)
	{
    	signal(SIGINT, handle_sigint);
    	signal(SIGQUIT, handle_sigquit);

    
    	str = readline("mini-flemme$ ");
    	if (!str || str[0] == '\0') 
    	{
    	    printf("exit\n");
    	    break;
    	}

    	token_list = tokenize(str);
    	if (!token_list)
    	{
     	add_history(str);
     	free(str);
     	continue;
    	}

    	exit_or_not(&token_list);

    	node = parse(&token_list);
    	ft_exe(node, env);

    	ft_free_all_node(&node);
    	ft_free_token(&token_list);
    	free(str);
	}
	clear_history();
	free(str);
	return (0);
}
