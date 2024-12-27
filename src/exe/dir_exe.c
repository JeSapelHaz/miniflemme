/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2024/12/27 21:46:57 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	input_dir(t_node *right, t_node *left, char **envp)
{
	int	fd;
	int	end[2];
	int	pid;
	int	status;

	pipe(end);
	fd = open(right->data.str, O_RDONLY);
	pid = fork();
	if (pid < 0)
	{
		perror("fork input fails");
		exit(1);
	}
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror(NULL);
			exit(1);
		}
		ft_exe_dir(left, envp, end);
		exit(excode);
	}
	close(fd);
	close(end[1]);
	close(end[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		excode = WEXITSTATUS(status);
}

void	output_dir(t_node *right, t_node *left, char **envp)
{
	int	fd;
	int	child;
	int	status;
	int	end[2];

	fd = open(right->data.str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("open file fails\n");
	pipe(end);
	child = fork();
	if (child < 0)
		exit(1);
	if (child == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror(NULL);
			exit(1);
		}
		close(fd);
		ft_exe_dir(left, envp, end);
		exit(excode);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
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

	fd = open(right->data.str, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd == -1)
		perror("open file fails\n");
	pipe(end);
	child = fork();
	if (child < 0)
		exit(1);
	if (child == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror(NULL);
			exit(1);
		}
		ft_exe_dir(left, envp, end);
		exit(excode);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		excode = WEXITSTATUS(status);
}

void	di_to_dir(t_node *right, t_node *left, char **envp)
{
	input_dir(right, left, envp);
	unlink(right->data.str);
}
