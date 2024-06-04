/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:53 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/04 12:26:57 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int lenofmyenv(char **env)
{
    int i = 0;
    int mylen = 0;

    while(env[i])
    {
        i++;
        mylen++;
    }
    return(mylen);

}

void exiterror(void)
{
    free_array(myenv);
    write(1, "\n", 1);
    return ;
}

char **creat_myenv()
{
    char **ptr;
    char buffer[PATH_MAX];

    ptr = (char **)malloc((4)*sizeof(char *));
    if(!ptr)
        exiterror();
    ptr[0] = ft_strjoin("PWD=", getcwd(buffer, PATH_MAX));
    ptr[1] = ft_strdup("SHLVL=1");
    ptr[2] = ft_strdup("_=/usr/bin/env");
    ptr[3] = NULL;
    return (ptr);
}

t_env	*env_last(t_env *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_env	*env_new(t_env *lst, char *str)
{
	t_env	*n_node;
	t_env	*last_node;

	n_node = (t_env *)malloc(sizeof(struct s_env));
	if (n_node == NULL)
		return (NULL);
	n_node->var_name = str;
	n_node->next = NULL;
	if (lst == NULL)
	{
		n_node->prev = NULL;
	}
	else
	{
		last_node = env_last(lst);
		n_node->prev = last_node;
	}
	return (n_node);
}

void    creat_env_list(t_env **list, char **env)
{
    t_env   *node;
    t_env   *curr;
    int i;

    i = 0;
    *list = env_new(*list, ft_strdup(env[i++]));
    while (env[i])
    {
        node = env_new(*list, ft_strdup(env[i++]));
		curr = env_last(*list);
		curr->next = node;
    }
}

t_env  *copieenv(char **env)
{
    t_env *list;

    list = NULL;
    if (!env[0])
    {
        env = creat_myenv();
        creat_env_list(&list, env);
        free(env[3]);
        free(env);
        return (list);
    }
    int len = lenofmyenv(env);
    myenv = (char **)malloc((len + 1)*sizeof(char *));
    if(!myenv)
        exiterror();
    
    int i = 0;
    while(env[i])
    {
        myenv[i] = ft_strdup(env[i]);
        if(!myenv[i])
        {
            exiterror();
        }
        i++;
    }
    myenv[i] = NULL;
    creat_env_list(&list, env);
    return (list);
}

void ft_putendle(char *str, int fd)
{
    if(!str)
		return;
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}

void printmyenv(t_env *list)
{
	while (list)
	{
		printf("%s\n", list->var_name);
		list = list->next;
	}
}
