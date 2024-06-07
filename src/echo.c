/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:36:48 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/07 10:45:37 by ksohail-         ###   ########.fr       */
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

void ft_echo(char **com, bool flag)
{
    int i = 0;

    if (!list->cmd[1])
    {
        printf("\n");
        return ;
    }
    if (com[0][0] == '-' && com[0][1] == 'n')
        flag = false;
    while (com[0][0] == '-')
    {
        if (check_n_flag(com[0] + 1) == true)
            com++;
        else
            break ;
    }
    while(com[i])
    {
        ft_putstr_fd(com[i], 1);
        ft_putchar_fd(' ', 1);
        i++; 
    }
    if (flag == true)
        printf("\n");
}
