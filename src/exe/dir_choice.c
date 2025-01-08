/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_choice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:37:30 by alama             #+#    #+#             */
/*   Updated: 2025/01/08 15:29:40 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	exe_pipe(t_node *node, char **envp)
{
	t_node	*left;
	t_node	*right;
	int		child1;
	int		child2;
	int		status;
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
	{
		dup2(end[1], STDOUT_FILENO);
		ft_exe_dir(left, envp, end);
		exit(g_excode);
	}
	waitpid(child1, &status, 0);
	child2 = fork();
	if (child2 < 0)
	{
		perror("fork child1 fails\n");
		exit(1);
	}
	if (child2 == 0)
	{
		dup2(end[0], STDIN_FILENO);
		ft_exe_dir(right, envp, end);
		exit(g_excode);
	}
	close(end[0]);
	close(end[1]);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
}

void	ft_exe_dir(t_node *node, char **env, int *end)
{
	t_node	*left;
	t_node	*right;

	if (node->type == STR_NODE)
		dir_process(node, env, end);
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
