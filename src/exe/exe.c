/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2025/01/06 15:54:36 by alama            ###   ########.fr       */
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
		execve(path, split_cmd, env);
		ft_execv_error(split_cmd);
	}
	ft_free_str(split_cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		excode = WEXITSTATUS(status);
}

void	dir_process(t_node *node, char **env, int *end)
{
	char	*path;
	char	**split_cmd;
	t_node	*tmp;

	//printf("here : %s\n", node->data.str);
	tmp = node;
	split_for_exe(tmp);
	split_cmd = ft_split(tmp->data.str, ' ');
	add_space_split(split_cmd);
	remove_quote(split_cmd);
	if (exec_builtin(split_cmd, env))
	{
		ft_free_str(split_cmd);
		exit(excode);
	}
	path = find_path(env, split_cmd);
	close(end[0]);
	close(end[1]);
	execve(path, split_cmd, env);
	ft_execv_error(split_cmd);
}

// en gros le vrai probleme c'etait que les builtins ils executaient dans un child
// donc par exemple si tu faisais en env et un export ca modifiait le child mais pas l'enfant
// du coup plutot que tout child comme je le faisais je fork seulement dans lexe et
// APRES la verrif de si c'est un builtins donc la ca remarche,
// j'ai du juste re-mettre des exit(0) dans les nouveaux childs et dans celui des pipes
void	ft_exe(t_node *node, char **env)
{
	t_node	*left;
	t_node	*right;

	if (node->type == STR_NODE)
		first_process(node, env);
	else if (node->type == PAIR_NODE)
	{
		left = node->data.pair.left;
		right = node->data.pair.right;
		if (node->data.pair.opera[0] == '|')
			exe_pipe(node, env);
		else if (ft_strncmp(node->data.pair.opera, "<", 2) == 0)
			input_dir(right, left, env);
		else if (ft_strncmp(node->data.pair.opera, ">", 2) == 0)
			output_dir(right, left, env);
		else if (ft_strncmp(node->data.pair.opera, ">>", 3) == 0)
			output_append(right, left, env);
		else if (ft_strncmp(node->data.pair.opera, "<<", 3) == 0)
			di_to_dir(right, left, env);
	}
}
