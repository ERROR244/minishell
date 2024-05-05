/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/05 06:52:56 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_file(char *str)
{
    if (access(str, F_OK) != 0)
    {
        ft_putstr_fd("minishel: ", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
    return (0);
}

int check_if_NULL(char *str)
{
    if (!str)
    {
        ft_putstr_fd("minishel: syntax error near unexpected token `newline'\n", 2);
        return (1);
    }
    return (0);
}
int check_for_pipe(t_cmds *cmds)
{
    if (!cmds->prev)
    {
        if (cmds->next && cmds->next->token == Pipe)
            ft_putstr_fd("minishel: syntax error near unexpected token `||'\n", 2);
        else
            ft_putstr_fd("minishel: syntax error near unexpected token `|'\n", 2);
        return (1);
    }
    return (0);
}
