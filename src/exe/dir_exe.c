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

char    *di_to_dir(t_node *right, t_node *left, char **envp)
{
	char	*delimiter;
	char	**split;
	char	*str;
	int		fd;
	char	*tmp;
    char    *invisible;

	split = ft_split(right->data.str, ' ');
	delimiter = split[0];
    printf("here is the deli : <%s>\n", delimiter);
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
    printf("here is the left : %s\n", left->data.str);
	ft_free_str(split);
    printf("here is the left : %s\n", left->data.str);
    if (!str)
        return (NULL);
    invisible = ft_strjoin(".", delimiter);
    printf("here is the invisible : %s\n", invisible);
    fd = open(invisible, O_CREAT | O_WRONLY, 0644);
    write(fd, str, ft_strlen(str));
    printf("here is the delimiter: %s\n", delimiter);
	close(fd);
    printf("here is the delimiter: %s\n", delimiter);
    free(delimiter);
    delimiter = ft_strjoin(left->data.str, str);
    printf("here is the delimiter: %s\n", delimiter);
    free(left->data.str);
    free(str);
    left->data.str = delimiter;
	first_process(left, envp);
    return (invisible);
}
