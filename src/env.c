/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:15:36 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 16:57:02 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void put_our_env(t_env **env, char *key, char *value)
{
    t_env *tmp;
    t_env *newnode = (t_env *)malloc(sizeof(t_env));

    newnode->key = ft_strdup(key);
    newnode->value = ft_strdup(value);
    newnode->next = NULL;
    
    if(*env == NULL)
    {
        *env = newnode;
    }
    else
    {
        tmp = *env;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newnode;
    }

}
void copy_the_envi(char **env, t_env *listenv)
{
    char **enviroment = env;

    char **split;
    while(*enviroment != NULL)
    {
        split  = ft_split(*enviroment, '=');
        put_our_env(&listenv, split[0], split[1]);
        enviroment++;
    }
}

void print_environment(t_data *data)
{
    t_env *env = data->env;
    while(env != NULL)
    {
       printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

