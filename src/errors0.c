/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 14:56:12 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errormsg_v1(char *str)
{
	ft_putstr_fd("minishel: syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (2);
}

int	errormsg_v2(char *str)
{
	ft_putstr_fd("minishel: syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (2);
}

int	check_for_pipe(t_cmds *cmds)
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
			if (cmds->next->token == Pipe)
				return (errormsg(" `||'\n"));
			else if (cmds->next->next && cmds->next->next->token == Pipe)
			{
				if (cmds->next->next->next
					&& cmds->next->next->next->token == Pipe)
					return (errormsg(" `||'\n"));
				return (errormsg(" `|'\n"));
			}
		}
		else if (!cmds->next || (cmds->next && cmds->next->token == Non
				&& !cmds->next->next))
			return (errormsg(" 'newline'\n"));
	}
	return (0);
}

int	check_quotation(char *str)
{
	char	c;
	int		i;

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

bool	check_eq(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	if (j == 0)
		return (true);
	return (false);
}
