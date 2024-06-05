/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:40:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/05 14:48:40 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void my_cd(t_env *list, char **com)
{
    int counter = morethan2arg(com);
    // printf("%d \n", counter);
    if(counter > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return ;
    }
    char *myhome = findmyvar(list, "HOME");
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
        printf("%s\n", cur);
    else
    {
        str = findmyvar(env, "PWD");
        printf("%s\n", str);
    }
}
