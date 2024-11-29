/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/29 17:11:49 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_handle_signals(int signal)
{
	(void)signal;
	// rl_replace_line("", 0);
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
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// int main(void) {
//     char *input;

//     input = readline("Test readline: ");
//     if (input) {
//         rl_replace_line("Replacement text", 0);
//         printf("Input replaced with: %s\n", rl_line_buffer);
//     }
//     return 0;
// }
