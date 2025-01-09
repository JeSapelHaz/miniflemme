/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/09 17:04:31 by alama            ###   ########.fr       */
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
