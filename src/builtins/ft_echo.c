/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:09 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/02 18:13:23 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vérifie si l'argument commence par "-n" suivi uniquement de n
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

// Fonction qui enlève les guillemets simples de la chaîne donnée.
char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;

	i = 0, j;
	i = 0, j = 0;
	if (!str)
		return (NULL);
	result = (char *)malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'')
		{
			result[j++] = str[i];
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

// Fonction qui compte le nombre de guillemets simples dans la chaîne.
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

// Fonction principale echo
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
	// Affiche un saut de ligne si l'option -n n'est pas utilisée
	if (newline)
		printf("\n");
}
