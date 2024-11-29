/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:25:24 by hbutt             #+#    #+#             */
/*   Updated: 2024/11/29 17:22:26 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void execute_commands(char *input, char **env) {
    char **commands;
    int i = 0;

    // Séparer les commandes par le délimiteur ';'
    commands = ft_split(input, ';'); 

    while (commands[i]) {
        char *command = commands[i];

        // Suppression des espaces en début et en fin de commande
        while (*command == ' ') command++;
        char *end = command + ft_strlen(command) - 1;
        while (end > command && *end == ' ') end--;
        *(end + 1) = '\0'; // Terminer la chaîne à la fin

        if (*command) { // Exécuter la commande seulement si elle n'est pas vide
            t_token *token_list = tokenize(command);
            char **cmd = ft_split(command, ' ');

            // Créer un processus fils pour exécuter la commande
            pid_t pid = fork();
            if (pid == 0) { // Processus fils
                execve(get_path(cmd[0], env), cmd, env);
                perror("execve"); // Si execve échoue
                exit(EXIT_FAILURE);
            } else if (pid < 0) { // Échec de fork
                perror("fork");
            } else { // Processus père
                int status;
                waitpid(pid, &status, 0); // Attendre que le fils termine
            }

            ft_free_token(&token_list);
            free(cmd);
        }
        i++;
    }
    free(commands);
}
