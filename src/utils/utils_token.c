/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:33:46 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/06 15:50:44 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

// void ft_add_next(t_token *last, t_token **token_list, t_token *new_node) {
//     if (!last || !new_node) return;

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