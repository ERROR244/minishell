/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:35 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/04 15:29:37 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_env *findmyindex(t_env *list, char *va)
{
    // int i = 0;
    // char *tmp;
    // tmp = ft_strjoin(va, "=");
    // if (tmp && tmp[0] == '=' && tmp[1] == '\0')
    // {
    //     free(tmp);
    //     tmp = NULL;
    // }
    // int len = ft_strlen(tmp);
    // while(myenv[i])
    // {
    //     if(ft_strncmp(myenv[i], tmp, len) == 0)
    //     {
    //             free(tmp);
    //             return(i);
    //     }
    //     i++;
    // }
    // free(tmp);
    // return (0);
    // list
    
    int len = ft_strlen(va);
    while(list)
    {
        if(ft_strncmp(list->var_name, va, len) == 0)
        {
            // free(tmp);
            return(list);
        }
        list = list->next;
    }
    return(NULL);
}


void set_myenv(t_env *list, char *key, char *value)
{
    t_env *index = findmyindex(list, key);
    t_env *node;
    char *tmp = ft_strjoin("=", value);

    
    
    
    
    if (index && (ft_strcmp(key, "OLDPWD") == 0 || ft_strcmp(key, "PWD") == 0))
    {
        free(index->var_name);
        if(value)
            index->var_name = ft_strjoin(key, tmp);
        else
            index->var_name = ft_strjoin(key, "=");
    }
    else if (!index || ft_strcmp(key, "OLDPWD") == 0)
    {
        if(value)
            node = env_new(list, ft_strjoin(key, tmp));
        else
            node = env_new(list, ft_strdup(key));
        if (!index)
        {
            list = env_last(list);
            list->next = node;
        }
        else
            index->next = node;
    }
    free(tmp);
}

void change_mydir(t_env *list, char *path)
{
    char *cur;
    char buffer[PATH_MAX];
    cur = getcwd(buffer, PATH_MAX);

    if(chdir(path) != 0)
    {
        perror("cd");
    }
    set_myenv(list, "PWD", path);
	set_myenv(list, "OLDPWD", cur);
}

char *findmyvar(t_env *list, char *va)
{
    char **vale;

    while(list)
    {
        vale = ft_split(list->var_name, '=');
        if(ft_strcmp(vale[0], va) == 0)
        {
            free_array(vale);
            return (ft_strchr(list->var_name, '=') + 1);
        }
        free_array(vale);
        if (!list->next)
            break ;
        list = list->next;
    }
    while (list)
    {
        if (!list->prev)
            break ;
        list = list->prev;
    }
    while (list)
    {
        if (ft_strncmp(list->var_name, "path", 3) == 0)
            return (NULL);
        list = list->next;
    }
    if (ft_strncmp(va, "path", 3) == 0)
        return ("/usr/bin");
    return (NULL);
}

int morethan2arg(char **com)
{
    int i = 0;
    int counter = 0;
    while(com[i])
    {
        i++;
        counter++;
    }
    return(counter);
}
