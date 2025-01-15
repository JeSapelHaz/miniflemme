/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/15 16:26:45 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_handle_signals(int signal)
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

static void	ft_handle_parent(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}

void	parent_signals(void)
{
	signal(SIGINT, ft_handle_parent);
}

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
}
