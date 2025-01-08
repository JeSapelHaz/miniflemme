/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2025/01/08 20:46:37 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// <
void	input_dir(t_node *right, t_node *left, char **envp, int *last)
{
	int	fd;
	int	end[2];
	char	*trim;
	int	pid;
	int	status;

	(void) last;
	trim = trim_file(right);
	fd = open(trim, O_RDONLY);
	pipe(end);
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(end[0]);
			close(end[1]);
			exit(0);
		}
		close(fd);
		free(trim);
		ft_exe_dir(left, envp, end);
		exit(g_excode);
	}
	close(end[0]);
	close(end[1]);
	free(trim);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
	if (fd > 0)
		close(fd);
	else
	{
		perror(" ");
		g_excode = 1;
	}
}

void	output_dir(t_node *right, t_node *left, char **envp, int *last)
{
	int		fd;
	int		child;
	int		status;
	int		end[2];
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
	if (pipe(end) == -1)
	{
		perror("pipe failed");
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
		if (last == NULL)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 failed");
				close(fd);
				exit(1);
			}
		}
		else
		{
			close(last[0]);
			close(last[1]);
		}
		close(fd);
		free(trim);
		ft_exe_dir(left, envp, end);
		exit(g_excode);
	}
	close(end[0]);
	close(end[1]);
	close(fd);
	free(trim);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
}

void	output_append(t_node *right, t_node *left, char **envp, int *last)
{
	int	fd;
	int	child;
	int	status;
	int	end[2];
	char	*trim;

	trim = trim_file(right);
	fd = open(trim, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd == -1)
	{
		perror("open failed");
		g_excode = 1;
		return ;
	}
	if (last == NULL)
	{
		if (pipe(end) == -1)
		{
			perror("pipe failed");
			g_excode = 1;
			return ;
		}
	}
	child = fork();
	if (child < 0)
	{
		perror("fork failed");
		g_excode = 1;
		return ;
	}
	if (child == 0)
	{
		if (last != NULL)
			dup2(fd, last[0]);
		else
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 failed");
				close(fd);
				exit(1);
			}
		}
		close(fd);
		free(trim);
		ft_exe_dir(left, envp, end);
		exit(g_excode);
	}
	close(fd);
	free(trim);
	close(end[0]);
	close(end[1]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
}

void	di_to_dir(t_node *right, t_node *left, char **envp, int *end)
{
	input_dir(right, left, envp, end);
	if (unlink(right->data.str) == -1)
		perror("unlink failed");
}
