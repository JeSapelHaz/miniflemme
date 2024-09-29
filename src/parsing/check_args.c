/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:38:25 by hbutt             #+#    #+#             */
/*   Updated: 2024/09/29 19:47:57 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

/**
 * @brief Verifie si les bon nombre d'arguments a eété introduit
 * 
 * @param ac le compteur d'args
 * @param av la string des args
 * @return 0 si bon nombre, ft_quit sinon
 */
int	check_args(int ac, char **av)
{
	if (ac > 1)
		ft_quit();
	(void)av;
	return (0);
}