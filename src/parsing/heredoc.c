/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:40:16 by alama             #+#    #+#             */
/*   Updated: 2024/11/23 18:25:06 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	gnl_heredoc(char *delimiter, int fd)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			break ;
		if (ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	exit(0);
}

void	heredoc_parse(t_token **token)
{
	t_token	*tmp;
	char	*doc;
	int		fd;
	int		status;

	tmp = (*token)->next;
	while (tmp->type == SPACE_TOKEN)
		tmp = tmp->next;
	doc = ft_strjoin(".", tmp->lexeme);
	fd = open(doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (free(doc), perror("open heredoc fails\n"), (void)NULL);
	status = fork();
	if (status == 0)
		gnl_heredoc(tmp->lexeme, fd);
	else
	{
		wait(NULL);
		free(tmp->lexeme);
		tmp->lexeme = doc;
	}
}
