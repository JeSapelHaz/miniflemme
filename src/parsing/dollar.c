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

// static char	*find_dollar(char *str, char **env)
// {
// 	int	i;
// 	//char	*tmp;

// 	//tmp = NULL;
// 	(void) env;
// 	i = 1;
// 	if (str[i] == '?')
// 		return (ft_itoa(excode));
// 	printf("nop\n");
// 	return (NULL);
// 	/*
// 	while (str[i])
// 	{
// 		if (str[i] == '?')
// 			return (ft_itoa(excode));
// 	}
// 	return (tmp);
// 	*/
// }

// static void	replace_dollar(t_node *node, char **env)
// {
// 	int	i;
// 	char	*answer;
// 	char	*tmp;
// 	char	*join;
// 	int	r;
// 	int	j;
// 	char	*last;

// 	i = 0;
// 	answer = NULL;
// 	while (node->data.str[i])
// 	{
// 		if (node->data.str[i] == '$')
// 		{
// 			answer = find_dollar(&node->data.str[i], env);
// 			tmp = malloc(sizeof(char) * i + 1);
// 			ft_strlcat(tmp, node->data.str, i);
// 			join = ft_strjoin(tmp, answer);
// 			r = i;
// 			while (node->data.str[r] != '\0' || node->data.str[r] != '<'
// 				|| node->data.str[r] != '>'
// 				|| node->data.str[r] != '|'
// 				|| node->data.str[r] != ')'
// 				|| node->data.str[r] != '('
// 				|| node->data.str[r] != '{'
// 				|| node->data.str[r] != '}'
// 				|| node->data.str[r] != '\\'
// 				|| node->data.str[r] != ']'
// 				|| node->data.str[r] != '?')
// 				r++;
// 			j = r;
// 			while (node->data.str[j])
// 				j++;
// 			j = j - r;
// 			last = malloc(sizeof(char) * j + 1);
// 			last[j + 1] = '\0';
// 			r = r - i;
// 			free(answer);
// 			free(node->data.str);
// 			node->data.str = ft_strjoin(join, last);
// 			free(last);
// 			free(join);
// 			break ;
// 		}		
// 		i++;
// 	}
// 	(void) env;
// }

// void	add_dollar(t_node *node, char **env)
// {
// 	if (node->type == STR_NODE)
// 		replace_dollar(node, env);
// 	else
// 	{
// 		if (node->data.pair.left)
// 			add_dollar(node->data.pair.left, env);
// 		if (node->data.pair.right)
// 			add_dollar(node->data.pair.right, env);
// 	}
// }

// void replace_dollar(t_node *node, char **env)
// {
// 	int i;

// 	i = 0;
// 	while(node->data.str[i])
// 		if (node->data.str[i] == '$')

// }



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

char	*replace_dollar_str(char *str, char **env)
{
	char	*result;
	char	*temp;
	int start;
	int		i;
	int  j;
	char	var_name[256];
	
	i = 0;
	start = 0;
	(void) start;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$') 
		{
			i++;
			start = i;
			j = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				var_name[j++] = str[i++];
			var_name[j] = '\0';

			char *var_value = get_env_value(var_name, env);

			temp = result;
			result = ft_strjoin(temp, var_value);
			free(temp);
		}
		else
		{
			char substr[2] = {str[i], '\0'};
			temp = result;
			result = ft_strjoin(temp, substr);
			free(temp);
			i++;
		}
	}
	return (result);
}

void	replace_dollar(t_node *node, char **env)
{
	char *new_str;

	if (!node || !node->data.str)
		return;
	new_str = replace_dollar_str(node->data.str, env);
	free(node->data.str);
	node->data.str = new_str;
}

void	add_dollar(t_node *node, char **env)
{
	if (!node)
		return;
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
