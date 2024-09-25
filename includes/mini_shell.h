/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:43 by alama             #+#    #+#             */
/*   Updated: 2024/09/25 19:48:39 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"

typedef enum e_node_type
{
	PAIR_NODE,
	CHAR_NODE
}	t_node_type;

typedef struct s_node	t_node;

typedef struct s_pair_value
{
	t_node		*left;
	t_node		*right;
}	t_pair_value;

typedef union u_node_value
{
	t_pair_value	pair;
	char			c;
}	t_node_value;

struct s_node
{
	t_node_type		type;
	t_node_value	data;
};

char	*get_path(char *cmd, char **env);

/* UTILS */

void	ft_error(char *msg);
void	ft_error_2(char *msg);
void	ft_free_tab(char **tab);
int		ft_compare_path(char *s1, char *s2);
int		open_file(char *file, int in_or_out);

#endif
