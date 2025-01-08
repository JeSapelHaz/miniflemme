/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:15 by alama             #+#    #+#             */
/*   Updated: 2025/01/02 17:46:35 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_env_value(char *var, char **env)
{
	int		i;
	size_t	var_len;

	if (!var || !env)
		return (NULL);
	var_len = strlen(var);
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], var, var_len) && env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return ("");
}

char	*itoa_exit_code(int n)
{
	char	*result;
	int		tmp;
	int		len;
	int		is_negative;

	len = (n <= 0);
	is_negative = (n < 0);
	tmp = n;
	while (tmp && ++len)
		tmp /= 10;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	if (is_negative)
		n = -n;
	while (n)
	{
		result[--len] = (n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		result[--len] = '-';
	return (result);
}
char	*handle_simple_dollar(char **result)
{
	char	substr[2];
	char	*temp;

	substr[0] = '$';
	substr[1] = '\0';
	temp = *result;
	*result = ft_strjoin(temp, substr);
	free(temp);
	return (*result);
}
char	*handle_exit_code(char **result)
{
	char	*temp;
	char	*exit_code_str;

	exit_code_str = itoa_exit_code(excode);
	if (!exit_code_str)
		return (NULL);
	temp = *result;
	*result = ft_strjoin(temp, exit_code_str);
	free(temp);
	free(exit_code_str);
	return (*result);
}

char	*handle_dollar(char **result, char *str, int *i, char **env)
{
	char	var_name[256];
	char	*var_value;
	char	*temp;
	int		j;

	(*i)++;
	if (str[*i] == '\0' || (str[*i] != '?' && !(ft_isalnum(str[*i])
				|| str[*i] == '_')))
		return (handle_simple_dollar(result));
	if (str[*i] == '?')
		return (handle_exit_code(result));
	j = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
	var_value = get_env_value(var_name, env);
	temp = *result;
	*result = ft_strjoin(temp, var_value);
	free(temp);
	return (*result);
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
		if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			result = add_char_to_result(result, str[i]);
		}
		else if (str[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			result = add_char_to_result(result, str[i]);
		}
		else if (str[i] == '$' && !in_single_quotes)
		{
			if (str[i + 1] == '?')
			{
				result = handle_exit_code(&result);
				i++;
			}
			else
			{
				result = handle_dollar(&result, str, &i, env);
				if (!result)
					return (NULL);
				continue ;
			}
		}
		else
		{
			result = add_char_to_result(result, str[i]);
			if (!result)
				return (NULL);
		}
		i++;
	}
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
