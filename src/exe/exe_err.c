/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:10:00 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 21:30:16 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fd_err(char **str)
{
	write(2, *str, ft_strlen(*str));
	write(2, ": ", 2);
	perror(NULL);
	g_excode = 1;
	free(*str);
	*str = NULL;
}

void	fork_err(char **str)
{
	perror("fork failed");
	g_excode = 1;
	free(*str);
	*str = NULL;
}
