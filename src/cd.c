/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:35 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 19:02:58 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int findmyindex(char *va)
{
    int i = 0;
    char *tmp;
    tmp = ft_strjoin(va, "=");
    if (tmp && tmp[0] == '=' && tmp[1] == '\0')
    {
        free(tmp);
        tmp = NULL;
    }
    int len = ft_strlen(tmp);
    while(myenv[i])
    {
        if(ft_strncmp(myenv[i], tmp, len) == 0)
        {
                free(tmp);
                return(i);
        }
        i++;
    }
    free(tmp);
    return(0);
}

void set_myenv(char *key, char *value)
{
    int myi = findmyindex(key);
    char *tmp = ft_strjoin("=", value);
    int i = 0;

    while (myenv[i])
        i++;
    if(myi != 0)
    {
        free(myenv[myi]);
        if(value)
            myenv[myi] = ft_strjoin(key, tmp);
        else
            myenv[myi] = ft_strjoin(key, "=");
    }
    else
    {
        myenv = (char **)realloc(myenv, (sizeof(char *) * i) + 8);
        if(value)
            myenv[i - 1] = ft_strjoin(key, tmp);
        else
            myenv[i - 1] = ft_strjoin(key, "= "" ");
        myenv[i] = NULL;
    }
    free(tmp);
}

void change_mydir(char *path)
{
    char *cur;
    char buffer[PATH_MAX];
    cur = getcwd(buffer, PATH_MAX);

    if(chdir(path) != 0)
    {
        perror("cd");
    }
	set_myenv("OLDPWD", cur);
    set_myenv("PWD", path);
}

char *findmyvar(char *va)
{
    int i = 0;
    char *tmp;
    char **vale;

    tmp = va;
    while(myenv[i])
    {
        vale = ft_split(myenv[i], '=');
        if(ft_strcmp(vale[0], tmp) == 0)
        {
            free_array(vale);
            return(ft_strchr(myenv[i], '=')) + 1;
        }
        free_array(vale);
        i++;
    }
    free(tmp);
    return(0);
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
