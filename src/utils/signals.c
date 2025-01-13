/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/13 15:45:23 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mini_shell.h"

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

void	ft_handle_signals(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	g_excode = 130;
	rl_redisplay();
}

void	initialize_signals(void)
{
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// void	ft_handle_signals(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_status = 130;
// 		if (g_user_input)
// 			ft_putstr_fd("\nminishell> ", 2);
// 		if (g_user_input)
// 			free(g_user_input);
// 		g_user_input = ft_strdup("\0");
// 	}
// 	else if (sig == SIGQUIT)
// 		write(2, "\b\b  \b\b", 6);
// }

// void	sig_init(void)
// {
// 	if (signal(SIGINT, ft_handle_signals) == SIG_ERR)
// 		exit(EXIT_FAILURE);
// 	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)
// 		exit(EXIT_FAILURE);
// }

// void	handle_exec_sig(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		if (g_user_input)
// 			free(g_user_input);
// 		g_status = 130;
// 		g_quit = 1;
// 		write(2, "\n", 1);
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		g_status = 131;
// 		ft_putstr_fd("Exit (core dumped)\n", 2);
// 	}
// }

// void	sig_exec_init(void)
// {
// 	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
// 		exit(EXIT_FAILURE);
// 	else if (signal(SIGQUIT, handle_exec_sig) == SIG_ERR)
// 		exit(EXIT_FAILURE);
// }
