/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:29:29 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/15 15:34:09 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			write(2, &str[i], 1);
		i++;
	}
}

static void	ft_execv_error(char **split_cmd)
{
	write(2, "mini-flemme: ", 13);
	ft_print(split_cmd[0]);
	if (split_cmd[0][0] == '/' || (split_cmd[0][0] == '.'
			&& split_cmd[0][1] == '/'))
	{
		ft_free_str(split_cmd);
		write(2, ": No such file or directory\n", 28);
		exit(126);
	}
	else
	{
		ft_free_str(split_cmd);
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

int	exec_builtin(char **args, char **env)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args), 1);
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
	t_node	*tmp;
	int		pid;
	int		status;

	tmp = node;
	split_for_exe(tmp);
	split_cmd = ft_split(tmp->data.str, ' ');
	add_space_split(split_cmd);
	remove_quote(split_cmd);
	if (exec_builtin(split_cmd, env))
	{
		ft_free_str(split_cmd);
		return ;
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork fails\n"));
	if (pid == 0)
	{
		path = find_path(env, split_cmd);
		g_excode = execve(path, split_cmd, env);
		ft_execv_error(split_cmd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
	ft_free_str(split_cmd);
}

void	dir_process(t_node *node, char **env, t_ctxt *ctxt)
{
	char *path;
	char **split_cmd;
	t_node *tmp;

	tmp = node;
	split_for_exe(tmp);
	split_cmd = ft_split(tmp->data.str, ' ');
	add_space_split(split_cmd);
	remove_quote(split_cmd);
	if (ctxt->infile != 0)
	{
		dup2(ctxt->infile, STDIN_FILENO);
		close(ctxt->infile);
	}
	if (ctxt->outfile != 1)
	{
		dup2(ctxt->outfile, STDOUT_FILENO);
		close(ctxt->outfile);
	}
	if (exec_builtin(split_cmd, env))
	{
		ft_free_str(split_cmd);
		exit(g_excode);
	}
	path = find_path(env, split_cmd);
	execve(path, split_cmd, env);
	ft_execv_error(split_cmd);
}