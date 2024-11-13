/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2024/11/13 21:05:33 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_execv_error(char **split_cmd)
{
	ft_free_str(split_cmd);
	perror(*split_cmd);
	exit(1);
}

static void	first_process(t_node *node, char **envp)
{
	char	*path;
	char	**split_cmd;
	//int		fd;
	//int		last;

	split_cmd = ft_split(node->data.str, ' ');
	//last = ft_last_word(split_cmd);
	//fd = open(split_cmd, O_RDONLY);
	path = find_path(envp, split_cmd);
	execve(path, split_cmd, envp);
	ft_execv_error(split_cmd);
}

void	pipe_left(t_node *right, t_node *left, int *end, char **envp)
{
	int		fd;

	//fd = open(right->data.str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd = open(right->data.str, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(right->data.str);
		exit(1);
	}
	if (dup2(end[STDOUT_FILENO], STDOUT_FILENO) == -1)
	{
		perror(NULL);
		exit(1);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	first_process(left, envp);
}

void	pipe_right(t_node *right, t_node *left, int *end, char **envp)
{
	int		fd;

	//fd = open(right->data.str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd = open(right->data.str, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
		perror("open file fails\n");
	if (dup2(end[STDIN_FILENO], STDIN_FILENO) == -1)
	{
		perror(right->data.str);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(NULL);
		exit(1);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	first_process(left, envp);
}

void	pipex(t_node *node, char **envp, int *end)
{
	int	child1;
	int	child2;
	t_node	*left;
	t_node	*right;

	left = node->data.pair.left;
	right = node->data.pair.right;
	pipe(end);
	child2 = 0;
	child1 = fork();
	if (child1 < 0)
		return (perror("fork fails\n"));
	if (child1 == 0)
		pipe_left(left->data.pair.right, left->data.pair.left, end, envp);
	else
	{
		child2 = fork();
		if (child2 < 0)
			return (perror("fork fails\n"));
		if (child2 == 0)
			pipe_right(right->data.pair.right, right->data.pair.left, end, envp);
	}
	close(end[0]);
	close(end[1]);
	wait(NULL);
	wait(NULL);
}

void	ft_exe(t_node *node, char **envp)
{
	int	status;
	int	end[2];

	pipe(end);
	status = fork();
	if (status < 0)
		return (perror("fork fails\n"));
	if (status == 0)
	{
		if (node->type == STR_NODE)
		{
			printf("it's a str\n");
			first_process(node, envp);
		}
		else if (node->type == PAIR_NODE
			&& node->data.pair.opera[0] == '|')
			pipex(node, envp, end);
	}
	close(end[1]);
	close(end[0]);
	wait(NULL);
}
