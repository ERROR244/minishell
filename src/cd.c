/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:15:50 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 16:40:02 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env *find_node(t_data *data, char *key)
{
    t_env *current = data->env;
    while(current != NULL)
    {
        if(ft_strcmp(current->key, key) == 0)
            return(current);
        current = current->next;
    }
    return(NULL);
}
void add_node(t_data **head, char  *key, char *value)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (new_node == NULL) {
        ft_putstr_fd("Error\n", 2);
        exit(1);
    }
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        t_env *current = (*head)->env;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// void updatethepwd(t_data *data, char *path)
// {
//     t_data *current = data;
//     while(current != NULL)
//     {
//         if(strcmp(current->key, "PWD") == 0)
//         {
//             printf("HERE\n");
//             current->value = ft_strjoin(current->value, path);
//         }
//         // printf("%s -> %s \n", path, current->value);
//         // if(strcmp(current->key, "OLDPWD") == 0)
//         //     current->value = ft_strdup(oldpath);
//         break;  
//         current = current->next;
//     }
// }

void ft_cd(char *str, t_data **data)
{
    t_env *current = (*data)->env;
    char cur[PATH_MAX];
    char *dir;
    dir = NULL;
    
    char **split = ft_split(str, ' ');
    if(split == NULL)
         return ;
    else if (split[1] == NULL)
    {
        while(current != NULL)
        {
            if(ft_strcmp(current->key, "HOME") == 0)
            {
                dir = current->value;
                break;
            }
            current= current->next;
        }
        chdir(dir);
    }
    else
    {
        if(split[2] != NULL)
            return ;
        dir = ft_strjoin(current->value, split[1]);
        chdir(split[1]);
    }
    // updatethepwd(*data, split[1]);
}