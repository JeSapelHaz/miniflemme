/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:26:22 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/15 15:27:31 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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

	exit_code_str = itoa_exit_code(g_excode);
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
