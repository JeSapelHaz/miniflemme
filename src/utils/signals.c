/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/04 16:12:28 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/mini_shell.h"

// void	handle_signal(int signal)
// {
// 	(void)signal;
// 	printf("\n");
// 	rl_on_new_line();       // Réinitialise la ligne de Readline
// 	rl_replace_line("", 0); // Efface la ligne actuelle
// 	rl_redisplay();			// Réaffiche lr prompt
// }
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