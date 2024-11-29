/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:19:12 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/25 18:02:22 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

#include <stdlib.h>

void ft_exit(char **args)
{
    int status = 0;
    if (args[1])
        status = ft_atoi(args[1]);
    exit(status); 
}
