/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:48:02 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/14 17:59:42 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "mini_shell.h"

// Prototype des fonctions builtins
void				ft_cd(char **args);
void				ft_echo(char **args);
void				ft_env(char **args);
void				ft_export(char **args);
void				ft_exit(char **args);
void				ft_pwd(char **args);
void				ft_unset(char **args);

// Définition du type de fonction pour les builtins
typedef void		(*t_builtin_func)(char **args);

// Structure associant le nom de chaque builtin à sa fonction
typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}					t_builtin;

// Tableau des builtins
t_builtin			g_builtins[] = {{"cd", ft_cd}, {"echo", ft_echo}, {"env",
				ft_env}, {"export", ft_export}, {"exit", ft_exit}, {"pwd",
				ft_pwd}, {"unset", ft_unset}};

#endif