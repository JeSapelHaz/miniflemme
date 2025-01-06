/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:16 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/06 14:24:47 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static size_t get_2d_array_size(char **array)
{
    size_t size = 0;
    while (array && array[size])
        size++;
    return (size);
}

static int is_valid_var_name(char *var)
{
    int i = 0;
    int equals_found = 0;

    if (!var || var[0] == '=')
        return (0);
    while (var[i] != '\0')
    {
        if (var[i] == '=')
        {
            if (equals_found)
                return (0);
            equals_found = 1;
            i++;
            break;
        }
        if (!((var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A' && var[i] <= 'Z') || var[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

static int var_exist(char *arg, char **env)
{
    int i = 0;
    size_t len = ft_strlen(arg);

    if (arg[len - 1] != '=')
        return (0);

    while (env[i])
    {
        if (ft_strncmp(env[i], arg, len) == 0)
            return (1);
        i++;
    }

    return (0);
}
static int find_var_index(char *arg, char **env)
{
    int i = 0;
    size_t len = ft_strlen(arg);

    while (env[i])
    {
        if (ft_strncmp(env[i], arg, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}

static char *get_var_name(char *env_var)
{
    int i = 0;
    while (env_var[i] && env_var[i] != '=')
        i++;
    return ft_substr(env_var, 0, i);
}

void ft_export(char **args, char ***env)
{
    int i = 1;
    int env_size = get_2d_array_size(*env);
    int index_env;

    if (args[1] == NULL)
    {
        i = 0;
        while ((*env)[i])
        {
            printf("declare x - %s\n", (*env)[i]);
            i++;
        }
        return;
    }

    while (args[i])
    {
        if (is_valid_var_name(args[i]))
        {
            if (var_exist(args[i], *env))
            {
                index_env = find_var_index(get_var_name(args[i]), *env);
				printf("indice %d\n", index_env);
				printf("indice %d %s\n", index_env, (*env)[index_env]);
                free((*env)[index_env]);
                (*env)[index_env] = ft_strdup(args[i]);
            }
            else
            {
                (*env)[env_size] = ft_strdup(args[i]);
                env_size++;
            }
        }
        else
        {
            write(2, "export: not a valid identifier\n", 31);
            excode = 1;
        }
        i++;
    }
}
