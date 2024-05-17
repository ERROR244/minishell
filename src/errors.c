/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/17 16:53:31 by ksohail-         ###   ########.fr       */
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

int  errormsg_v1(char *str)
{
    ft_putstr_fd("minishel: syntax error near unexpected token '", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("'\n", 2);
    return (1);
}

int check_file(t_cmds *cmds)
{
    if (access(cmds->cmd, F_OK) != 0)
    {
        ft_putstr_fd("minishel: ", 2);
        ft_putstr_fd(cmds->cmd, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
    else if (access(cmds->cmd, R_OK) != 0)
    {
        ft_putstr_fd("minishel: ", 2);
        ft_putstr_fd(cmds->cmd, 2);
        ft_putstr_fd(": Permission denied\n", 2);
        return (1);
    }
    cmds->data->outfile = open(cmds->cmd, O_RDONLY, 0666);
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
    if (!cmds->prev || cmds->prev->token == Non)
    {
        if (cmds->next && cmds->next->token == Pipe)
            return (errormsg(" `||'\n"));
        return (errormsg(" `|'\n"));
    }
    else if (cmds->prev && cmds->prev->token != Pipe)
    {
        if (cmds->next && cmds->next->token == Pipe)
        {
            if (cmds->next->next && cmds->next->next->token == Pipe)
            {
                if (cmds->next->next->next && cmds->next->next->next->token == Pipe)
                    return (errormsg(" `||'\n"));
                return (errormsg(" `|'\n"));
            }
        }
    }
    // else if (cmds->prev && cmds->prev->token == Non)
    // {
    //     if (cmds->next && cmds->next->token == Pipe)
    //         return (errormsg(" `||'\n"));
    //     return (errormsg(" `|'\n"));
    // }
    return (0);
}
