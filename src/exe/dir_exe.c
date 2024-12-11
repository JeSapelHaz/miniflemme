/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2024/12/11 14:27:48 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	input_dir(t_node *right, t_node *left, int *end, char **envp)
{
	int	fd;

	fd = open(right->data.str, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(right->data.str);
		exit(1);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	if (left->type == PAIR_NODE)
		ft_exe(left, envp, end);
	else
		first_process(left, envp);
}

void	output_dir(t_node *right, t_node *left, int *end, char **envp)
{
	int	fd;

	fd = open(right->data.str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("open file fails\n");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(NULL);
		exit(1);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	if (left->type == PAIR_NODE)
		ft_exe(left, envp, end);
	else
		first_process(left, envp);
}

void	output_append(t_node *right, t_node *left, int *end, char **envp)
{
	int	fd;

	fd = open(right->data.str, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd == -1)
		perror("open file fails\n");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(NULL);
		exit(1);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	if (left->type == PAIR_NODE)
		ft_exe(left, envp, end);
	else
		first_process(left, envp);
}

void	di_to_dir(t_node *right, t_node *left, int *end, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		input_dir(right, left, end, envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		excode = WEXITSTATUS(status);
	unlink(right->data.str);
}
