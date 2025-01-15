/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:15 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 16:23:32 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	toggle_quote_flags(char c, int *in_single_quotes,
		int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}

static char	*handle_dollar_and_result(char *result, char *str, int *i,
		char **env, int in_single_quotes)
{
	if (str[*i] == '$' && !in_single_quotes)
	{
		if (str[*i + 1] == '?')
		{
			result = handle_exit_code(&result);
			(*i)++;
		}
		else
		{
			result = handle_dollar(&result, str, i, env);
			if (!result)
				return (NULL);
		}
	}
	else
	{
		result = add_char_to_result(result, str[*i]);
	}
	return (result);
}

static char	*process_char(char *result, char c, int *in_single_quotes,
		int *in_double_quotes)
{
	toggle_quote_flags(c, in_single_quotes, in_double_quotes);
	result = add_char_to_result(result, c);
	return (result);
}

char	*replace_dollar_str(char *str, char **env)
{
	char	*result;
	int		i;
	int		in_single_quotes;
	int		in_double_quotes;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	in_single_quotes = 0;
	in_double_quotes = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && result)
		{
			result = process_char(result, str[i], &in_single_quotes,
					&in_double_quotes);
		}
		else
		{
			result = handle_dollar_and_result(result, str, &i, env,
					in_single_quotes);
		}
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

void	replace_dollar(t_node *node, char **env)
{
	int		i;
	int		var_found;
	char	*new_str;

	if (!node || !node->data.str)
		return ;
	i = 0;
	var_found = 0;
	while (env[i])
	{
		if (!ft_strncmp(node->data.str, env[i], ft_strlen(node->data.str))
			&& env[i][ft_strlen(node->data.str)] == '=')
		{
			var_found = 1;
			break ;
		}
		i++;
	}
	if (!var_found && (ft_strncmp(node->data.str, "$?", 2) == 0))
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
