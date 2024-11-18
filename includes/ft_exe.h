/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:54:33 by alama             #+#    #+#             */
/*   Updated: 2024/11/18 18:46:28 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXE_H
# define FT_EXE_H

# include "mini_shell.h"

void	ft_exe(t_node *node, char **envp);
char	*find_path(char **envp, char **cmd);
void	ft_free_str(char **str);
void	pipex(t_node *node, char **envp, int *end);
void	pipe_right(t_node *right, t_node *left, int *end, char **envp);
void	pipe_left(t_node *right, t_node *left, int *end, char **envp);
// que passa si je fais une cmd genre cmd >> file > file
void	input_dir(t_node *right, t_node *left, int *end, char **envp);
void	output_dir(t_node *right, t_node *left, int *end, char **envp);
void	output_append(t_node *right, t_node *left, int *end, char **envp);
void	first_process(t_node *node, char **envp);
void	di_to_dir(t_node *right, t_node *left, char **envp);

#endif
