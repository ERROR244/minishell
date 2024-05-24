/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/24 17:14:59 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int  errormsg_v1(char *str)
{
    ft_putstr_fd("minishel: syntax error near unexpected token '", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("'\n", 2);
    return (1);
}

int check_file(t_cmds *cmds)
{
    if (access(cmds->cmd[0], F_OK) != 0)
    {
        ft_putstr_fd("minishel: ", 2);
        ft_putstr_fd(cmds->cmd[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
    else if (access(cmds->cmd[0], R_OK) != 0)
    {
        ft_putstr_fd("minishel: ", 2);
        ft_putstr_fd(cmds->cmd[0], 2);
        ft_putstr_fd(": Permission denied\n", 2);
        return (1);
    }
    // cmds->data->outfile = open(cmds->cmd[0], O_RDONLY, 0666);
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
        else if (!cmds->next || (cmds->next && cmds->next->token == Non))
            return (errormsg(" 'newline'\n"));
    }
    return (0);
}

int	check_quotation(char *str)
{
	char c;
	int i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			c = str[i];
			while (str[++i])
			{
				if (str[i] == c)
					break ;
			}
		}
		if (str[i] == '\0')
		{
        	errormsg(" 'newline'\n");
			return (-1);
		}
	}
	return (0);
}
