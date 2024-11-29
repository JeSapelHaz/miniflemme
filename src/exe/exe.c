/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2024/11/29 17:42:00 by hbutt            ###   ########.fr       */
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

int	exec_builtin(char **args, char **env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args), 1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args), 1);
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args, env), 1);
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, &env), 1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args), 1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, &env), 1);
	return (0);
}

void	first_process(t_node *node, char **env)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(node->data.str, ' ');
	if (exec_builtin(split_cmd, env))
		return ;
	path = find_path(env, split_cmd);
	execve(path, split_cmd, env);
	ft_execv_error(split_cmd);
}

void	pipe_process(t_node *node, char **env, int *end)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(node->data.str, ' ');
	if (exec_builtin(split_cmd, env))
		return ;
	path = find_path(env, split_cmd);
	close(end[0]);
	close(end[1]);
	execve(path, split_cmd, env);
	ft_execv_error(split_cmd);
}

void	ft_exe(t_node *node, char **env)
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
			first_process(node, env);
		else if (node->type == PAIR_NODE)
		{
			left = node->data.pair.left;
			right = node->data.pair.right;
			if (node->data.pair.opera[0] == '|')
				exe_pipe(node, env, end);
			if (ft_strncmp(node->data.pair.opera, "<", 2) == 0)
				input_dir(right, left, end, env);
			if (ft_strncmp(node->data.pair.opera, ">", 2) == 0)
				output_dir(right, left, end, env);
			if (ft_strncmp(node->data.pair.opera, ">>", 3) == 0)
				output_append(right, left, end, env);
			if (ft_strncmp(node->data.pair.opera, "<<", 3) == 0)
				di_to_dir(right, left, end, env);
		}
		exit(0);
	}
	close(end[1]);
	close(end[0]);
	wait(NULL);
}
