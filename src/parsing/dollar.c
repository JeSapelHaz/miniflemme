/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:15 by alama             #+#    #+#             */
/*   Updated: 2024/12/11 18:17:16 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*find_dollar(char *str, char **env)
{
	int	i;
	//char	*tmp;

	//tmp = NULL;
	(void) env;
	i = 1;
	if (str[i] == '?')
		return (ft_itoa(excode));
	printf("nop\n");
	return (NULL);
	/*
	while (str[i])
	{
		if (str[i] == '?')
			return (ft_itoa(excode));
	}
	return (tmp);
	*/
}

static void	replace_dollar(t_node *node, char **env)
{
	int	i;
	char	*answer;
	char	*tmp;
	char	*join;
	int	r;
	int	j;
	char	*last;

	i = 0;
	answer = NULL;
	while (node->data.str[i])
	{
		if (node->data.str[i] == '$')
		{
			answer = find_dollar(&node->data.str[i], env);
			tmp = malloc(sizeof(char) * i + 1);
			ft_strlcat(tmp, node->data.str, i);
			join = ft_strjoin(tmp, answer);
			r = i;
			while (node->data.str[r] != '\0' || node->data.str[r] != '<'
				|| node->data.str[r] != '>'
				|| node->data.str[r] != '|'
				|| node->data.str[r] != ')'
				|| node->data.str[r] != '('
				|| node->data.str[r] != '{'
				|| node->data.str[r] != '}'
				|| node->data.str[r] != '\\'
				|| node->data.str[r] != ']'
				|| node->data.str[r] != '?')
				r++;
			j = r;
			while (node->data.str[j])
				j++;
			j = j - r;
			last = malloc(sizeof(char) * j + 1);
			last[j + 1] = '\0';
			r = r - i;
			free(answer);
			free(node->data.str);
			node->data.str = ft_strjoin(join, last);
			free(last);
			free(join);
			break ;
		}		
		i++;
	}
	(void) env;
}

void	add_dollar(t_node *node, char **env)
{
	if (node->type == STR_NODE)
		replace_dollar(node, env);
	else
	{
		if (node->data.pair.left)
			add_dollar(node->data.pair.left, env);
		if (node->data.pair.right)
			add_dollar(node->data.pair.right, env);
	}
}
