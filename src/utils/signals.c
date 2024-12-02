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

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// void	rl_replace_line(const char *text, int clear_undo);
// void	rl_clear_history(void);

void	handle_sigint(int sig)
{
    (void)sig;
	write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void	handle_sigquit(int sig)
{
    (void)sig;
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
//             break;
//         }
//         add_history(str);
//         free(str);
//     }
//     return (0);
// }
