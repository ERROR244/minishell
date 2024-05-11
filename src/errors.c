/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/11 23:46:44 by error01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_put2str_fd(char *s1, char *s2, int fd)
{
	if (fd >= 0 && s1 && s2)
	{
		while (*s1)
		{
			ft_putchar_fd(*s1, fd);
			s1++;
		}
        while (*s2)
		{
			ft_putchar_fd(*s2, fd);
			s2++;
		}
	}
}

int  errormsg(char *str)
{
    ft_put2str_fd("minishel: syntax error near unexpected token", str, 2);
    return (1);
}

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
        return (errormsg(" `newline'\n"));
    return (0);
}

int check_for_pipe(t_cmds *cmds)
{
    if (!cmds->prev)
    {
        if (cmds->next && cmds->next->token == Pipe)
            return (errormsg(" `||'\n"));
        return (errormsg(" `|'\n"));
    }
    if (cmds->prev && cmds->prev->token != Pipe)
    {
        if (cmds->next && cmds->next->token == Pipe)
        {
            if (cmds->next->next && cmds->next->next->token == Pipe)
            {
                if (cmds->next->next->next && cmds->next->next->next->token == Pipe)
                    return (errormsg(" `||'\n"));
                return (errormsg(" `|'\n"));
            }
            else
                return (11);
        }
        return (0);
    }
    return (0);
}
