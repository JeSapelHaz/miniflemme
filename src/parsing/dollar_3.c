/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:26:25 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/15 16:20:54 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
	return ("");
}

static int	ft_get_length(int n)
{
	int	len;

	len = (n <= 0);
	while (n && ++len)
		n /= 10;
	return (len);
}

static void	ft_fill_number(char *result, int n, int is_negative)
{
	int	len;

	len = ft_get_length(n);
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
}

char	*itoa_exit_code(int n)
{
	char	*result;
	int		is_negative;
	int		len;

	is_negative = (n < 0);
	len = ft_get_length(n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_fill_number(result, n, is_negative);
	return (result);
}
