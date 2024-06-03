/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:53 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/03 18:30:49 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env *env_list = NULL;

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

void    creat_myenv()
{
    char buffer[PATH_MAX];

    myenv = (char **)malloc((4)*sizeof(char *));
    if(!myenv)
        exiterror();
    myenv[0] = ft_strjoin("PWD=", getcwd(buffer, PATH_MAX));
    myenv[1] = ft_strdup("SHLVL=1");
    myenv[2] = ft_strdup("_=/usr/bin/env");
    myenv[3] = NULL;
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

void    creat_env_list(char **env)
{
    t_env   *node;
    t_env   *curr;
    int i;

    i = 0;
    env_list = env_new(env_list, env[i++]);
    while (env[i])
    {
        node = env_new(env_list, env[i++]);
		curr = env_last(env_list);
		curr->next = node;
    }
}

void  copieenv(char **env)
{
    if (!env[0])
    {
        creat_myenv();
        return ;
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
    creat_env_list(myenv);
}

void ft_putendle(char *str, int fd)
{
    if(!str)
		return;
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}

void printmyenv()
{
    int		i;

	i = 0;

	while (myenv[i])
    {
		ft_putendle(myenv[i], 1);
        i++;
    }
    // printlistenv(env_list);
}
