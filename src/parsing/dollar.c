/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:15 by alama             #+#    #+#             */
/*   Updated: 2025/01/16 17:25:26 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*replace_dollar_str(char *str, char **env)
{
	return (process_chars(str, env));
}

char	*get_env_value(char *var, char **env)
{
	int		i;
	size_t	var_len;

	if (!var || !env)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, var_len) && env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return (" ");
}

char	*add_char_to_result(char *result, char c)
{
	char	substr[2];
	char	*temp;

	substr[0] = c;
	substr[1] = '\0';
	temp = result;
	result = ft_strjoin(temp, substr);
	free(temp);
	return (result);
}

void	replace_dollar(t_node *node, char **env)
{
	char	*new_str;

	if (!node || !node->data.str)
		return ;
	new_str = replace_dollar_str(node->data.str, env);
	free(node->data.str);
	node->data.str = new_str;
}

void	add_dollar(t_node *node, char **env)
{
	if (!node)
		return ;
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
