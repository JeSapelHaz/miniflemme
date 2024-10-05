/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/05 14:27:40 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
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