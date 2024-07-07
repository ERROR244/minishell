/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:53 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 08:41:42 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
    char    *str;
    char    **ptr;
    int     subshell;
    t_env   *node;
    t_env   *curr;
    int i;

    i = 0;
    subshell = 0;
    *list = env_new(*list, ft_strdup(env[i++]));
    while (env[i])
    {
        if (ft_strncmp("SHLVL", env[i], 4) == 0)
        {
            ptr = ft_split(env[i++], '=');
            subshell = ft_atoi(ptr[1]);
            str = ft_itoa(++subshell);
            free_array(ptr);
            node = env_new(*list, ft_strjoin3("SHLVL", '=', str));
            free(str);
        }
        else
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
        free_array(env);
        return (list);
    }
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
    int i;
    bool flag;

	while (list)
	{
        i = 0;
        flag = false;
        while (list->var_name[i])
        {
            if (list->var_name[i] == '=')
            {
                flag = true;
                break ;
            }
            i++;
        }
        if (flag == true)
        {
            ft_putstr_fd(list->var_name, 1);
            ft_putchar_fd('\n', 1);
        }
		list = list->next;
	}
}
