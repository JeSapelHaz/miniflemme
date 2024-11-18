/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2024/11/18 23:18:10 by alama            ###   ########.fr       */
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

void	gnl_heredoc(int *end, char *delimiter)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			break ;
		if (ft_strlen(delimiter) == 0 && str[0] == '\n')
			return (free(str), exit(0));
		if (ft_strlen(delimiter) > 0 && ft_strncmp(str, delimiter,
				ft_strlen(delimiter)) == 0)
		{
			free(str);
			break ;
		}
		write(end[1], str, ft_strlen(str));
		write(end[1], "\n", 1);
		free(str);
	}
	close(end[1]);
	close(end[0]);
	exit(0);
}

void	di_to_dir(t_node *right, t_node *left, char **envp)
{
	int		end[2];
	int		status;

	pipe(end);
	status = fork();
	if (status < 0)
		return (perror("fork fails\n"));
	if (status == 0)
		gnl_heredoc(end, right->data.str);
	else
	{
		printf("im here\n");
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		wait(NULL);
		first_process(left, envp);
	}
}
