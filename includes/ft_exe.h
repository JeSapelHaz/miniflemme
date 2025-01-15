/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:54:33 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 15:59:57 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXE_H
# define FT_EXE_H

# include "mini_shell.h"

void	ft_exe(t_node *node, char **envp);
char	*find_path(char **envp, char **cmd);
void	ft_free_str(char **str);
void	pipex(t_node *node, char **envp, t_ctxt *ctxt);
void	pipe_right(t_node *right, t_node *left, char **envp);
void	pipe_left(t_node *right, t_node *left, char **envp);
// que passa si je fais une cmd genre cmd >> file > file
void	input_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt);
void	output_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt);
void	output_append(t_node *right, t_node *left, char **envp, t_ctxt *ctxt);
void	first_process(t_node *node, char **envp);
void	di_to_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt);
void	exe_pipe(t_node *node, char **envp, t_ctxt *ctxt);
void	split_for_exe(t_node *node);
void	add_space_split(char **data);
void	remove_quote(char **data);
void	ft_exe_dir(t_node *node, char **env, t_ctxt *ctxt);
void	dir_process(t_node *node, char **env, t_ctxt *ctxt);
char	*trim_file(t_node *node);

#endif
