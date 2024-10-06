/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_node_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:03 by hbutt             #+#    #+#             */
/*   Updated: 2024/10/06 18:26:46 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

/* DEBUG FONCTION CREE  A L AIDE DE CHAT GPT */
#include <stdio.h>

void print_tree(t_node *root) {
    if (root == NULL) return; // Vérifier si le nœud est NULL

    // Si le nœud est un pipeline
    if (root->type == PIPELINE_NODE) {
        printf("Pipeline:\n");
        printf(" Left -> ");
        print_tree(root->left); // Imprimer le sous-arbre gauche
        printf(" Right -> ");
        print_tree(root->right); // Imprimer le sous-arbre droit
    } 
    // Si le nœud est une commande
    else if (root->type == COMMAND_NODE) {
        printf("Command: ");
        if (root->args) {
            for (int i = 0; root->args[i] != NULL; i++) {
                printf("%s", root->args[i]);
                if (root->args[i + 1] != NULL) {
                    printf(" "); // Ajouter un espace entre les arguments
                }
            }
        }
        printf("\n");
    }
}

