/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:33:46 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/06 19:32:54 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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
