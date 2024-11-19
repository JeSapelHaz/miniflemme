/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2024/11/19 20:34:46 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_execv_error(char **split_cmd)
{
	write(1, "mini-flemme: ", 13);
	write(1, split_cmd[0], ft_strlen(split_cmd[0]));
	write(1, ": command not found\n", 20);
	ft_free_str(split_cmd);
	exit(1);
}
int	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args), 1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args), 1);
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args), 1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args), 1);
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args), 1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args), 1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args), 1);
	return (0);
}

void	first_process(t_node *node, char **envp)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(node->data.str, ' ');
	if (exec_builtin(split_cmd))
		return ;
	path = find_path(envp, split_cmd);
	execve(path, split_cmd, envp);
	ft_execv_error(split_cmd);
}

void	pipe_left(t_node *right, t_node *left, int *end, char **envp)
{
	int	fd;

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
	int	fd;

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

void	exe_pipe(t_node *node, char **envp, int *end)
{
	int		child1;
	int		child2;
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
	{
		if (dup2(end[STDOUT_FILENO], STDOUT_FILENO) == -1)
		{
			perror(NULL);
			exit(1);
		}
		if (left->type == STR_NODE)
			first_process(left, envp);
		close(end[0]);
		close(end[1]);
	}
	else
	{
		child2 = fork();
		if (child2 < 0)
			return (perror("fork fails\n"));
		if (child2 == 0)
		{
			if (dup2(end[STDIN_FILENO], STDIN_FILENO) == -1)
			{
				perror(NULL);
				exit(1);
			}
			if (right->type == STR_NODE)
				first_process(right, envp);
			close(end[0]);
			close(end[1]);
		}
	}
	close(end[0]);
	close(end[1]);
	wait(NULL);
	wait(NULL);
	exit(0);
}

void	ft_exe(t_node *node, char **envp)
{
	int		status;
	int		end[2];
	t_node	*left;
	t_node	*right;

	pipe(end);
	status = fork();
	if (status < 0)
		return (perror("fork fails\n"));
	if (status == 0)
	{
		if (node->type == STR_NODE)
			first_process(node, envp);
		else if (node->type == PAIR_NODE)
		{
			left = node->data.pair.left;
			right = node->data.pair.right;
			if (node->data.pair.opera[0] == '|')
				exe_pipe(node, envp, end);
			if (ft_strncmp(node->data.pair.opera, "<", 2) == 0)
				input_dir(right, left, end, envp);
			if (ft_strncmp(node->data.pair.opera, ">", 2) == 0)
				output_dir(right, left, end, envp);
			if (ft_strncmp(node->data.pair.opera, ">>", 3) == 0)
				output_append(right, left, end, envp);
	    	if (ft_strncmp(node->data.pair.opera, "<<", 3) == 0)
				di_to_dir(right, left, envp);
        }
	}
	close(end[1]);
	close(end[0]);
	wait(NULL);
}
