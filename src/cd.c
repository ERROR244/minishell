/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:35 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/09 20:30:14 by ksohail-         ###   ########.fr       */
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
            return(list);
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

void    set_env_after_export(t_env *list, char *key, char *value, char c, bool export_flag)
{
    t_env   *index;
    t_env   *node;
    char    *tmp;

    index = findmyindex(list, key);
    if (index)
    {
        if (c == '+')
        {
            tmp = ft_strjoin(index->var_name, value);
            free(index->var_name);
            index->var_name = ft_strjoin(index->var_name, value);
        }
        else
        {
            if (ft_strcmp(index->var_name, value) != 0 || export_flag == true)
            {
                free(index->var_name);
                index->var_name = ft_strjoin3(key, '=', value);
            }
        }
        return ;
    }
    node = env_new(list, ft_strjoin3(key, '=', value));
    list = env_last(list);
    list->next = node;
}

void    set_env_after_cd(t_env *list, char *key, char *value)
{
    t_env   *index;
    t_env   *node;
    char    *tmp;

    index = findmyindex(list, key);
    if (index && (ft_strcmp(key, "OLDPWD") == 0 || ft_strcmp(key, "PWD") == 0))
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
    else if (!index && (ft_strcmp(key, "PWD") == 0 || ft_strcmp(key, "OLDPWD") == 0))
    {
        node = env_new(list, ft_strjoin3(key, '=', value));
        list = env_last(list);
        list->next = node;
    }
}

void change_mydir(t_env *list, char *path)
{
    char *cur;
    char buffer[PATH_MAX];

    cur = findmyvar(list, list, "PWD", false);
    if(chdir(path) != 0)
        perror("cd");
    else
    {
    	set_env_after_cd(list, "OLDPWD", cur);
        set_env_after_cd(list, "PWD", getcwd(buffer, PATH_MAX));
    }
}

char *findmyvar(t_env *list, t_env *head, char *va, bool flag)
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
    while (head)
    {
        if (ft_strncmp(head->var_name, "path", 3) == 0)
            return (NULL);
        head = head->next;
    }
    if (ft_strncmp(va, "PATH", 3) == 0 && flag == true)
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
