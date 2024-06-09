/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:40:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/09 17:52:40 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void my_cd(t_env *list, char **com)
{
    char *myhome;
    int counter;
    
    counter = morethan2arg(com);
    if(counter > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return ;
    }
    myhome = findmyvar(list, list, "HOME", false);
    if(com[1] == NULL || com[1][0] == '~')
    {
        if (!myhome)
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        else
            change_mydir(list, myhome);
    }
    else 
        change_mydir(list, com[1]);
}

void mypwd(t_env *env)
{
    char buffer[PATH_MAX];
    char *cur;
    char *str;

    cur = getcwd(buffer, PATH_MAX);
    if (cur)
    {
        ft_putstr_fd(cur, 1);
        ft_putchar_fd('\n', 1);
    }
    else
    {
        str = findmyvar(env, env, "PWD", false);
        ft_putstr_fd(str, 1);
        ft_putchar_fd('\n', 1);
    }
}
