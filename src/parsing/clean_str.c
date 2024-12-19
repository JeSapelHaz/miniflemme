/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:25:14 by hbutt             #+#    #+#             */
/*   Updated: 2024/12/19 17:25:19 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mini_shell.h"

char *remove_backslashes(const char *str) {
    if (!str)
        return NULL;

    char *result = malloc(strlen(str) + 1); // Alloue de la mémoire pour la nouvelle chaîne
    if (!result)
        return NULL;

    char *write_ptr = result;
    while (*str) {
        if (*str == '\\' && *(str + 1)) {
            str++; // Ignore le backslash et passe au caractère suivant
        }
        *write_ptr++ = *str++;
    }
    *write_ptr = '\0'; // Terminaison de la chaîne
    return result;
}


void clean_str_nodes(t_node *node) {
    if (!node)
        return;

    if (node->type == STR_NODE) {
        char *cleaned_str = remove_backslashes(node->data.str);
        free(node->data.str);        // Libère l'ancienne chaîne
        node->data.str = cleaned_str; // Affecte la nouvelle chaîne nettoyée
    } else if (node->type == PAIR_NODE) {
        clean_str_nodes(node->data.pair.left);
        clean_str_nodes(node->data.pair.right);
    }
}
