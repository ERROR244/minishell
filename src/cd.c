/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:35 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/04 15:58:05 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_env *findmyindex(t_env *list, char *va)
{
    int len;
    
    len = ft_strlen(va);
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
    char *tmp;
    
    tmp = NULL;
    
    if (index && (ft_strcmp(key, "OLDPWD") == 0 || ft_strcmp(key, "PWD") == 0))                 //  update oldpwd or pwd if they exist in the envirment list
    {
        free(index->var_name);
        index->var_name = ft_strjoin(key, "=");
        if(value)
        {
            tmp = index->var_name;
            index->var_name = ft_strjoin(index->var_name, value);
            free(tmp);
        }
    }
    else if (!index && (ft_strcmp(key, "PWD") == 0 || ft_strcmp(key, "OLDPWD") == 0))             //  creat oldpwd or pwd in the envirment list if they don't exist in the envirment list
    {
        tmp = ft_strjoin("=", value);
        node = env_new(list, ft_strjoin(key, tmp));
        list = env_last(list);
        list->next = node;
        free(tmp);
    }
    else if (!index)
    {
        tmp = ft_strjoin("=", value);
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
        free(tmp);
    }
}

void change_mydir(t_env *list, char *path)
{
    char *cur;
    char buffer[PATH_MAX];

    cur = getcwd(buffer, PATH_MAX);
    // printf("%s \n", cur);
	set_myenv(list, "OLDPWD", cur);
    if(chdir(path) != 0)
        perror("cd");
    else
        set_myenv(list, "PWD", getcwd(buffer, PATH_MAX));
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
    if (ft_strncmp(va, "PATH", 3) == 0)
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
