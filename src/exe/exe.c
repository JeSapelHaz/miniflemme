/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2024/11/08 23:26:14 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

/*
static int	ft_last_word(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
		i++;
	return (i);
}
*/

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

void	ft_exe(t_node *node, char **envp)
{
	//int	end[2];
	int	status;
	
	//pipe(end);
	status = fork();
	if (status < 0)
		return (perror("fork fails\n"));
	if (status == 0)
	{
		if (node->type == STR_NODE)
			first_process(node, envp);
	}
	wait(NULL);
}
