/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:49:57 by alama             #+#    #+#             */
/*   Updated: 2024/09/28 17:35:07 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/mini_shell.h"

// static	void	ft_add_next(t_token *last, t_token **stack, t_token *new_node)
// {
// 	while (last->next != *stack)
// 		last = last->next;
// 	last->next = new_node;
// 	new_node->prev = last;
// 	(*stack)->prev = new_node;
// }

// static void	ft_if_not_last(t_token **stack, t_token **new_node)
// {
// 	(*stack)->next = *new_node;
// 	(*stack)->prev = *new_node;
// 	(*new_node)->prev = *stack;
// }



// void	token_set(char *str, t_token **token)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\n')
// 			ft_add_token(token, END_TOKEN, "salut");
// 		// else if (str[i] == ' ')
// 		// 	ft_add_token(&token, SPACE_TOKEN, &str[i]);
// 		// else if (str[i] == '(')
// 		// 	ft_add_token(&token, LPARAN_TOKEN, &str[i]);
// 		// else if (str[i] == ')')
// 		// 	ft_add_token(&token, RPARAN_TOKEN, &str[i]);
// 		// else if (str[i] == '\'')
// 		// 	ft_add_token(&token, SINGLE_QUOTE, &str[i]);
// 		// else if (str[i] == '\"')
// 		// 	ft_add_token(&token, DOUBLE_QUOTE, &str[i]);
// 		// else if (str[i] == '|')
// 		// 	ft_add_token(&token, PIPE, &str[i]);
// 		// else if (str[i] == '>')
// 		// 	ft_add_token(&token, O_DIR, &str[i]);
// 		// else if (str[i] == '<')
// 		// 	ft_add_token(&token, I_DIR, &str[i]);
// 		// else
// 		// 	ft_add_token(&token, CHAR_TOKEN, &str[i]);
// 		i++;
// 	}
// }

// // int	main(void)
// // {
// // 	t_token	**token= NULL;
// // 	(*token) = NULL;
// // 	// printf("ok");
// // 	token_set("salut les amis comment vous allez haz", token);
// // 	// char *str = "salut";
// // 	// ft_add_token(&token, END_TOKEN, str);
// // 	// token->type = SINGLE_QUOTE;
// // 	// token->lexeme = "ok";
// // 	// printf("ok");
// // 	printf("%s\n", (*token)->lexeme);
// // 	printf("%u\n", (*token)->type);
// // 	// while(token->next)
// // 	// 	printf("%s", token->lexeme);
// // 	return (0);
// // }
