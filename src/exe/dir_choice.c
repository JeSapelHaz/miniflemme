/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_choice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:37:30 by alama             #+#    #+#             */
/*   Updated: 2024/12/22 14:13:01 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	exe_pipe(t_node *node, char **envp, int *end)
{
	int		child1;
	int		child2;
	t_node	*left;
	t_node	*right;
	int		status;

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
			pipe_process(left, envp, end);
		else
			ft_exe(left, envp, end);
		exit(excode);
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
				pipe_process(right, envp, end);
			else
				ft_exe(right, envp, end);
			exit(excode);
		}
	}
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		excode = WEXITSTATUS(status);
}
