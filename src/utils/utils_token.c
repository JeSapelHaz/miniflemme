/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:33:46 by hbutt             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/07 15:41:30 by alama            ###   ########.fr       */
=======
/*   Updated: 2024/10/06 15:45:51 by hbutt            ###   ########.fr       */
>>>>>>> a4a4d4f5df4e6dc03f6e3eeb1452aeddd0af5141
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

<<<<<<< HEAD
void	ft_add_next(t_token *last, t_token **token_list, t_token *new_node)
{
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	(*token_list)->prev = new_node;
}
=======
// void ft_add_next(t_token *last, t_token **token_list, t_token *new_node) {
//     if (!last || !new_node) return;
>>>>>>> a4a4d4f5df4e6dc03f6e3eeb1452aeddd0af5141

//     last->next = new_node;   // Relier le dernier nœud au nouveau
//     new_node->prev = last;   // Relier le nouveau nœud au dernier nœud
//     new_node->next = NULL;   // Le nouveau nœud doit pointer vers NULL
// }


// void ft_if_not_last(t_token **token_list, t_token **new_node) {
//     if (!token_list || !(*token_list) || !(*new_node)) return;

//     (*token_list)->next = *new_node;  // Relier le nœud courant au nouveau
//     (*new_node)->prev = *token_list;   // Relier le nouveau nœud au courant
//     (*new_node)->next = NULL;           // Le nouveau nœud doit pointer vers NULL
// }


static void ft_del(t_token *token) {
    if (token) {
        token->next = NULL;
        token->prev = NULL;
        free(token);
    }
}
/** 
 * elle libère la mémoire existante de la liste de token 
 */
void ft_free_token(t_token **token_list) {
    t_token *tmp;

    if (!token_list || !(*token_list)) return;

    // Libérer tous les nœuds jusqu'à ce que nous atteignions NULL
    while (*token_list) {
        tmp = (*token_list)->next; // Stocker le nœud suivant
        ft_del(*token_list);       // Libérer le nœud courant
        *token_list = tmp;         // Passer au nœud suivant
    }
}


// void	find_last_token(t_token **token_list)
// {
// 	if (!token_list)
// 		return (NULL);
// 	t_token *current = token_list;
// 	while (current->next && current->next != token_list)
// 	{
// 		current = current->next;
// 	}
// 	return (current);
// }
