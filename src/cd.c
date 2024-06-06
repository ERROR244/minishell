/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:35 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/06 11:26:52 by ksohail-         ###   ########.fr       */
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

char	*ft_strjoin3(char const *s1, char c, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (s1 == NULL && s2 != NULL)
		return (ft_strdup((char *)s2));
	if (s2 == NULL && s1 != NULL)
		return (ft_strdup((char *)s1));
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (ptr == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

void insert_var_node_in_list(t_env *index, t_env *node)
{
    if (index && node)
    {
        node->next = index->next;
        node->prev = index;
        
        if (index->next)
            index->next->prev = node;
        
        index->next = node;
    }
}


void set_myenv(t_env *list, char *key, char *value, char c)
{
    t_env *index = findmyindex(list, key);
    t_env *node;
    char *tmp;

    if (index && (ft_strcmp(key, "OLDPWD") == 0 || ft_strcmp(key, "PWD") == 0))                   //  update oldpwd or pwd if they exist in the envirment list.
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
    else if (!index && (ft_strcmp(key, "PWD") == 0 || ft_strcmp(key, "OLDPWD") == 0))             //  creat oldpwd or pwd in the envirment list if they don't exist in the envirment list.
    {
        node = env_new(list, ft_strjoin3(key, '=', value));
        list = env_last(list);
        list->next = node;
    }
    else if (!index)                                                                              //    this part is for export command for a key don't have a value.
    {
        node = env_new(list, ft_strjoin3(key, '=', value));
        list = env_last(list);
        list->next = node;
    }
    else if (index)                                                                               //    this part is for export command for a key do have a value.
    {
        if (c == '+')                                                                             //    this sub-part is for Append export
        {
            // printf("%s - %s \n", key, value);
            tmp = ft_strjoin(index->var_name, value);
            free(index->var_name);
            index->var_name = tmp;
        }
        else                                                                                      //    this sub-part is for non-Append export
        {
            free(index->var_name);
            index->var_name = ft_strjoin3(key, '=', value);
        }
    }
}

void change_mydir(t_env *list, char *path)
{
    char *cur;
    char buffer[PATH_MAX];

    cur = getcwd(buffer, PATH_MAX);
    if(chdir(path) != 0)
        perror("cd");
    else
    {
    	set_myenv(list, "OLDPWD", cur, '-');
        set_myenv(list, "PWD", getcwd(buffer, PATH_MAX), '-');
    }
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
