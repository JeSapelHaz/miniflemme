/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2024/12/04 14:43:52 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "mini_shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

void	ft_handle_signals(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	initialize_signals(void)
{
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

// int	main(void)
// {
//     char	*str;

//     signal(SIGINT, handle_sigint);
//     signal(SIGQUIT, handle_sigquit);

//     while (1)
//     {
//         str = readline("mini-flemme$ ");
//         if (!str)  // Gérer Ctrl-D
//         {
//             printf("exit\n");
//             break ;
//         }
//         add_history(str);
//         free(str);
//     }
//     return (0);
// }
