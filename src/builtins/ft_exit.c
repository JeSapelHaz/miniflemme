/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:19:12 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/14 17:49:31 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

#include <stdlib.h>

void ft_exit(char **args)
{
    int status = 0;
    if (args[1])
        status = ft_atoi(args[1]); // Convertir l'argument en entier pour le code de sortie
    exit(status); // Quitter le programme avec le code de sortie spécifié
}
