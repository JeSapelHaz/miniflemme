/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:54:33 by alama             #+#    #+#             */
/*   Updated: 2024/11/08 23:24:28 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXE_H
# define FT_EXE_H

# include "mini_shell.h"

void	ft_exe(t_node *node, char **envp);
char	*find_path(char **envp, char **cmd);
void	ft_free_str(char **str);

#endif
