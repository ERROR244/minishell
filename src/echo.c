/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:36:48 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/09 14:57:35 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool    check_n_flag(char *str)
{
    while (str && *str)
    {
        if (*str != 'n')
            return (false);
        str++;
    }
    return (true);
}

void ft_echo(char **com, bool flag, int i, int fd)
{
    if (!com[0])
    {
        ft_putstr_fd("\n", fd);
        return ;
    }
    if (com[0][0] == '-' && com[0][1] == 'n')
        flag = true;
    while (com[0][0] == '-')
    {
        if (check_n_flag(com[0] + 1) == true)
        {
            flag = false;
            com++;
        }
        else
            break ;
    }
    while(com[i])
    {
        ft_putstr_fd(com[i++], fd);
        ft_putchar_fd(' ', fd);
    }
    if (flag == true)
        ft_putstr_fd("\n", fd);
}
