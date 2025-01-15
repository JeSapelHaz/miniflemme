/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 15:34:29 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// <
void	input_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	int		fd;
	char	*trim;
	int		pid;
	int		status;

	trim = trim_file(right);
	fd = open(trim, O_RDONLY);
	if (fd < 0)
	{
		perror(" ");
		g_excode = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (ctxt->is_first_i == 0)
		{
			ctxt->infile = fd;
			ctxt->is_first_i = 1;
		}
		free(trim);
		ft_exe_dir(left, envp, ctxt);
		exit(g_excode);
	}
	close(fd);
	free(trim);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
}

void	output_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	int		fd;
	int		child;
	int		status;
	char	*trim;

	trim = trim_file(right);
	fd = open(trim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, trim, ft_strlen(trim));
		write(2, ": ", 2);
		perror(NULL);
		g_excode = 1;
		free(trim);
		return ;
	}
	child = fork();
	if (child < 0)
	{
		perror("fork failed");
		g_excode = 1;
		free(trim);
		return ;
	}
	if (child == 0)
	{
		if (ctxt->is_first_o == 0)
		{
			ctxt->outfile = fd;
			ctxt->is_first_o = 1;
		}
		free(trim);
		ft_exe_dir(left, envp, ctxt);
		exit(g_excode);
	}
	close(fd);
	free(trim);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
}

void	output_append(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	int		fd;
	int		child;
	int		status;
	char	*trim;

	trim = trim_file(right);
	fd = open(trim, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd == -1)
	{
		write(2, trim, ft_strlen(trim));
		write(2, ": ", 2);
		perror(NULL);
		g_excode = 1;
		free(trim);
		return ;
	}
	child = fork();
	if (child < 0)
	{
		perror("fork failed");
		g_excode = 1;
		free(trim);
		return ;
	}
	if (child == 0)
	{
		if (ctxt->is_first_o == 0)
		{
			ctxt->outfile = fd;
			ctxt->is_first_o = 1;
		}
		free(trim);
		ft_exe_dir(left, envp, ctxt);
		exit(g_excode);
	}
	close(fd);
	free(trim);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
}

void	di_to_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	input_dir(right, left, envp, ctxt);
	if (unlink(right->data.str) == -1)
		perror("unlink failed");
}
