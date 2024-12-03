/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_choice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:37:30 by alama             #+#    #+#             */
/*   Updated: 2024/11/25 12:48:11 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
			pipe_process(left, envp, end);
		else
			ft_exe(left, envp, end);
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
		}
	}
	close(end[0]);
	close(end[1]);
	wait(NULL);
	wait(NULL);
	exit(0);
}

/*
void	ft_dir_choice(t_node *node, char **envp)
{
	
}
*/
