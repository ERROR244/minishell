/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:40:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 18:44:58 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void my_cd(char **com)
{
    int counter = morethan2arg(com);
    printf("%d \n", counter);
    if(counter > 2)
    {
        ft_putstr_fd("cd: too many arguments", 1);
        exit(1);
    }
    char *myhome = findmyvar("HOME");
    if(com[1] == NULL || com[1][0] == '~')
        change_mydir(myhome);
    else 
        change_mydir(com[1]);
}

void mypwd(void)
{
    char *cur;
    char buffer[PATH_MAX];
    cur = getcwd(buffer, PATH_MAX);
    printf("%s\n", cur);
}

void ft_putendexp(char *str, int fd)
{
    char	*tmp;

    if(!str)
            return ;
	tmp = ft_strjoin(str, "\n");
    ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}
