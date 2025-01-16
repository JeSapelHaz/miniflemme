/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:15 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/16 17:27:16 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*process_chars(char *str, char **env)
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
		if (is_quote(str[i], in_double_quotes, in_single_quotes))
			result = handle_quotes_logic(result, str[i], &in_single_quotes,
					&in_double_quotes);
		else if (!in_single_quotes && str[i] == '$')
			result = handle_dollars_logic(result, str, &i, env);
		else
			result = handle_char_logic(result, str[i]);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
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
