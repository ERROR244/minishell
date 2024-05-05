/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/05 22:34:44 by ksohail-         ###   ########.fr       */
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

// ls | ls      ->good
// ls || ls     ->cmds == ls
// ls ||| ls    ->SError '|'
// ls |||| ls   ->SError '||'

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
    if (cmds->prev && cmds->prev->token != Pipe)
    {
        if (cmds->next && cmds->next->token != Pipe)
            return (0);
        else if (cmds->next && cmds->next->token == Pipe)
        {
            if (cmds->next->next && cmds->next->next->token == Pipe)
            {
                if (cmds->next->next->next && cmds->next->next->next->token == Pipe)
                {
                    ft_putstr_fd("minishel: syntax error near unexpected token `||'\n", 2);
                    return (1);
                }
                ft_putstr_fd("minishel: syntax error near unexpected token `|'\n", 2);
                return (1);
            }
            else
                return (11);
        }
    }
    return (0);
}
