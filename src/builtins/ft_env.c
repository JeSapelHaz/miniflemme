/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:12 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/05 14:19:37 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void ft_env(char *args, char **env)
{
	(void) args;
	while(*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
}