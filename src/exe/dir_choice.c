/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_choice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:37:30 by alama             #+#    #+#             */
/*   Updated: 2025/01/14 19:47:02 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	child_left(t_node *left, char **envp, int end[2], t_ctxt *ctxt)
{
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	ft_exe_dir(left, envp, ctxt);
	exit(g_excode);
}

void	child_right(t_node *right, char **envp, int end[2], t_ctxt *ctxt)
{
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(end[0]);
	ft_exe_dir(right, envp, ctxt);
	exit(g_excode);
}
/*
void	exe_pipe(t_node *node, char **envp, t_ctxt *ctxt)
{
	int	end[2];
	int	pid_left;
	int	pid_right;
	int	status1;
	int	status2;

	if((pipe(end)) == -1)
	{
		perror("Broken pipe\n");
		exit(1);
	}
	pid_left = fork();
	if (pid_left < 0)
	{
		perror("fork child1 fails\n");
		exit(1);
	}
	if (pid_left == 0)
		child_left(node->data.pair.left, envp, end, ctxt);
	waitpid(pid_left, &status1, 0);
	pid_right = fork();
	if (pid_right < 0)
	{
		perror("fork child1 fails\n");
		exit(1);
	}
	if (pid_right == 0)
		child_right(node->data.pair.right, envp, end, ctxt);
	close(end[1]);
	close(end[0]);
	waitpid(pid_right, &status2, 0);
	if (WIFEXITED(status2))
		g_excode = WEXITSTATUS(status2);
	else
		g_excode = 1;
}
*/

void	exe_pipe(t_node *node, char **envp, t_ctxt *ctxt)
{
	t_node	*left;
	t_node	*right;
	int		child1;
	int		child2;
	int		status;
	int		status2;
	int		end[2];

	left = node->data.pair.left;
	right = node->data.pair.right;
	pipe(end);
	child1 = fork();
	if (child1 < 0)
	{
		perror("fork child1 fails\n");
		exit(1);
	}
	if (child1 == 0)
		child_left(left, envp, end, ctxt);
	child2 = fork();
	if (child2 < 0)
	{
		perror("fork child1 fails\n");
		exit(1);
	}
	if (child2 == 0)
		child_right(right, envp, end, ctxt);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status2, 0);
	if (WIFEXITED(status2))
		g_excode = WEXITSTATUS(status2);
	else
		g_excode = 1;
}

void	ft_exe_dir(t_node *node, char **env, t_ctxt *ctxt)
{
	t_node	*left;
	t_node	*right;

	if (node->type == STR_NODE)
		dir_process(node, env, ctxt);
	else if (node->type == PAIR_NODE)
	{
		left = node->data.pair.left;
		right = node->data.pair.right;
		if (node->data.pair.opera[0] == '|')
			exe_pipe(node, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<", 2) == 0)
			input_dir(right, left, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">", 2) == 0)
			output_dir(right, left, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">>", 3) == 0)
			output_append(right, left, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<<", 3) == 0)
			di_to_dir(right, left, env, ctxt);
	}
}
