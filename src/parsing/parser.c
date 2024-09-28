/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:49:57 by alama             #+#    #+#             */
/*   Updated: 2024/09/28 15:47:23 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static	void	ft_add_next(t_token *last, t_token **stack, t_token *new_node)
{
	while (last->next != *stack)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	(*stack)->prev = new_node;
}

static void	ft_if_not_last(t_token **stack, t_token **new_node)
{
	(*stack)->next = *new_node;
	(*stack)->prev = *new_node;
	(*new_node)->prev = *stack;
}

void	ft_add_token(t_token **token, t_token_type type, char *lexeme)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		ft_free_token(token);
		exit(printf("malloc from tokens fails\n"));
	}
	new_token->type = type;
	new_token->lexeme = lexeme;
	if (!token || !*token)
	{
		new_token->prev = NULL;
		new_token->next = NULL;
		*token = new_token;
		return ;
	}
	last = (*token)->next;
	new_token->next = *token;
	if (!last)
		ft_if_not_last(token, &new_token);
	else
		ft_add_next(last, token, new_token);
}

void	token_set(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			ft_add_token(&token, END_TOKEN, &str[i]);
		else if (str[i] == ' ')
			ft_add_token(&token, SPACE_TOKEN, &str[i]);
		else if (str[i] == '(')
			ft_add_token(&token, LPARAN_TOKEN, &str[i]);
		else if (str[i] == ')')
			ft_add_token(&token, RPARAN_TOKEN, &str[i]);
		else if (str[i] == '\'')
			ft_add_token(&token, SINGLE_QUOTE, &str[i]);
		else if (str[i] == '\"')
			ft_add_token(&token, DOUBLE_QUOTE, &str[i]);
		else if (str[i] == '|')
			ft_add_token(&token, PIPE, &str[i]);
		else if (str[i] == '>')
			ft_add_token(&token, O_DIR, &str[i]);
		else if (str[i] == '<')
			ft_add_token(&token, I_DIR, &str[i]);
		else
			ft_add_token(&token, CHAR_TOKEN, &str[i]);
		i++;
	}
}

int	main(void)
{
	t_token	*token;

	token = NULL;
	token_set("coucou comment ca va la team ?\n", token);
	printf("%s\n", token->lexeme);
	// while(token->next)
	// 	printf("%s", token->lexeme);
	return (0);
}
