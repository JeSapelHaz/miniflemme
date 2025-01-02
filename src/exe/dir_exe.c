/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2025/01/02 17:17:27 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	input_dir(t_node *right, t_node *left, char **envp)
{
	int		fd;
	int		end[2];
	int		pid;
	int		status;
	char	*trim;

	if (pipe(end) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	trim = trim_file(right);
	fd = open(trim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	fd = open(trim, O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			close(fd);
			exit(1);
		}
		close(fd);
		ft_exe_dir(left, envp, end);
		free(trim);
		exit(excode);
	}
	close(fd);
	close(end[1]);
	close(end[0]);
	free(trim);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		excode = WEXITSTATUS(status);
}

void	output_dir(t_node *right, t_node *left, char **envp)
{
	int		fd;
	int		child;
	int		status;
	int		end[2];
	char	*trim;

	if (pipe(end) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	trim = trim_file(right);
	fd = open(trim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	child = fork();
	if (child < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if (child == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			close(fd);
			exit(1);
		}
		close(fd);
		close(end[0]);
		close(end[1]);
		ft_exe_dir(left, envp, end);
		free(trim);
		exit(excode);
	}
	close(end[0]);
	close(end[1]);
	close(fd);
	free(trim);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		excode = WEXITSTATUS(status);
}

void	output_append(t_node *right, t_node *left, char **envp)
{
	int	fd;
	int	child;
	int	status;
	int	end[2];

	if (pipe(end) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	fd = open(right->data.str, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	child = fork();
	if (child < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if (child == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			close(fd);
			exit(1);
		}
		close(fd);
		close(end[0]);
		close(end[1]);
		ft_exe_dir(left, envp, end);
		exit(excode);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
	{
		excode = WEXITSTATUS(status);
	}
}

void	di_to_dir(t_node *right, t_node *left, char **envp)
{
	input_dir(right, left, envp);
	if (unlink(right->data.str) == -1)
	{
		perror("unlink failed");
	}
}
