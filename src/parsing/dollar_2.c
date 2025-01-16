/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:17:39 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/16 17:27:46 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_quote(char c, int in_double_quotes, int in_single_quotes)
{
	return ((c == '\'' && !in_double_quotes) || (c == '"'
			&& !in_single_quotes));
}

void	toggle_quote_state(char c, int *in_single_quotes,
		int *in_double_quotes)
{
	if (c == '\'')
		*in_single_quotes = !*in_single_quotes;
	else if (c == '"')
		*in_double_quotes = !*in_double_quotes;
}

char	*handle_quotes_logic(char *result, char c, int *in_single_quotes,
		int *in_double_quotes)
{
	toggle_quote_state(c, in_single_quotes, in_double_quotes);
	return (add_char_to_result(result, c));
}

char	*handle_char_logic(char *result, char c)
{
	return (add_char_to_result(result, c));
}

char	*handle_dollars_logic(char *result, char *str, int *i, char **env)
{
	if (str[*i + 1] == '?')
	{
		result = handle_exit_code(&result);
		(*i)++;
	}
	else
		result = handle_dollar(&result, str, i, env);
	return (result);
}
