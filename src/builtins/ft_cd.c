/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:07 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/14 17:49:02 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


void ft_cd(char **args)
{
    if (!args[1])
    {
        fprintf(stderr, "minishell: cd: missing argument\n");
        return;
    }
    if (chdir(args[1]) != 0)
    {
        perror("minishell: cd");
    }
}
