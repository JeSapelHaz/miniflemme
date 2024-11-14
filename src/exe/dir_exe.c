/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2024/11/14 21:51:17 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	input_dir(t_node *right, t_node *left, int *end, char **envp)
{
	int		fd;

	fd = open(right->data.str, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(right->data.str);
		exit(1);
	}
	close(fd);
	close(end[0]);
	close(end[1]);
	first_process(left, envp);
}

void	output_dir(t_node *right, t_node *left, int *end, char **envp)
{
	int		fd;

	fd = open(right->data.str, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
		perror("open file fails\n");
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

void	output_append(t_node *right, t_node *left, int *end, char **envp)
{
	int		fd;

	fd = open(right->data.str, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd == -1)
		perror("open file fails\n");
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

void	di_to_dir(t_node *right, t_node *left, char **envp)
{
	char	*delimiter;
	char	**split;
	char	*str;
	int		fd;
	char	*tmp;

	split = ft_split(right->data.str, ' ');
	delimiter = split[0];
	str = NULL;
	while (1)
	{
		tmp = readline("> ");
		if (ft_strncmp(tmp, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(tmp);
			break ;
		}
		str = ft_strjoin(str, tmp);
		free(tmp);
	}

	ft_free_str(split);
	close(fd);
	first_process(left, envp);
}
