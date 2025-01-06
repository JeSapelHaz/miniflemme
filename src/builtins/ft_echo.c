/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:09 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/06 10:17:01 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	is_valid_n_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	int		double_quotes_count;
	int		single_quotes_count;

	i = 0;
	j = 0;
	double_quotes_count = 0;
	single_quotes_count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			double_quotes_count++;
		if (str[i] == '\'')
			single_quotes_count++;
		i++;
	}
	i = 0;
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && double_quotes_count % 2 == 0)
		{
			i++; // Skip double quotes
			continue ;
		}
		if (str[i] == '\'' && single_quotes_count % 2 == 0)
		{
			i++; // Skip single quotes
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	ft_numbers_of_singlequotes(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nbr++;
		i++;
	}
	return (nbr);
}

void	ft_echo(char **args)
{
	int		i;
	int		newline;
	char	*arg_without_quotes;

	i = 1;
	newline = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		if ((ft_numbers_of_singlequotes(args[i]) % 2) == 0)
		{
			arg_without_quotes = remove_quotes(args[i]);
			if (arg_without_quotes)
			{
				printf("%s", arg_without_quotes);
				free(arg_without_quotes);
			}
		}
		else
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
