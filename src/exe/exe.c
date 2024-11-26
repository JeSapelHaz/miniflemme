/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2024/11/26 14:34:38 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_execv_error(char **split_cmd)
{
	write(2, "mini-flemme: ", 13);
	write(2, split_cmd[0], ft_strlen(split_cmd[0]));
	write(2, ": command not found\n", 20);
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
	t_node	*tmp;

	tmp = node;
	//while (tmp->type == PAIR_NODE)
//		tmp = tmp->data.pair.left;
	split_cmd = ft_split(tmp->data.str, ' ');
	if (exec_builtin(split_cmd))
		return ;
	path = find_path(envp, split_cmd);
	execve(path, split_cmd, envp);
	ft_execv_error(split_cmd);
}

void	pipe_process(t_node *node, char **envp, int *end)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(node->data.str, ' ');
	if (exec_builtin(split_cmd))
		return ;
	path = find_path(envp, split_cmd);
	close(end[0]);
	close(end[1]);
	execve(path, split_cmd, envp);
	ft_execv_error(split_cmd);
}

void	ft_exe(t_node *node, char **envp, int *end)
{
	int		status;
	t_node	*left;
	t_node	*right;

	if (end[0] == 0)
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
					di_to_dir(right, left, end, envp);
        	}
		close(end[1]);
		close(end[0]);
		exit(0);
	}
	close(end[1]);
	close(end[0]);
	wait(NULL);
}
