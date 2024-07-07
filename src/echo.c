/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:36:48 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 08:42:04 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exiterror(void)
{
    write(1, "error\n", 7);
    return ;
}

bool    check_n_flag(char *str)
{
    str++;
    while (str && *str)
    {
        if (*str != 'n')
            return (false);
        str++;
    }
    return (true);
}

void ft_echo(char **com, bool flag, int i)
{
    if (!com[0])
    {
        ft_putstr_fd("\n", 1);
        return ;
    }
    if (com[0][0] == '-' && com[0][1] == 'n')
    {
        flag = true;
        while (com[0] && com[0][0] == '-')
        {
            if (check_n_flag(com[0]) == true)
            {
                flag = false;
                com++;
            }
            else
                break ;
        }
    }
    while(com[i])
    {
        ft_putstr_fd(com[i++], 1);
        if (com[i])
            ft_putchar_fd(' ', 1);
    }
    if (flag == true)
        ft_putstr_fd("\n", 1);
}

char **creat_myenv()
{
    char **ptr;
    char buffer[PATH_MAX];

    ptr = (char **)malloc((4) * sizeof(char *));
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
