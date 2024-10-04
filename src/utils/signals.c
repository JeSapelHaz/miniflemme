/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:05:03 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/02 14:17:18 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	handle_signal(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();       // Réinitialise la ligne de Readline
	rl_replace_line("", 0); // Efface la ligne actuelle
	rl_redisplay();			// Réaffiche lr prompt
}
