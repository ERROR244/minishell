/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:12:43 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/25 11:36:43 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void token1(t_cmds *cmds, char c)
{
	if (c == '<')
	{
		if (cmds->prev && cmds->prev->token == Non)
			cmds->prev->token = Cmd;
		if (cmds->next && cmds->next->token == Non)
			cmds->next->token = Infile;
		cmds->token = Input;
	}
	else if (c == '>')
	{
		if (cmds->prev && cmds->prev->token == Non)
			cmds->prev->token = Cmd;
		if (cmds->next && cmds->next->token == Non)
			cmds->next->token = OutFile;
		cmds->token = Output;
	}

	else if (c == '|')
	{
		if (cmds->prev && cmds->prev->token == Non)
			cmds->prev->token = Cmd;
		if (cmds->next && cmds->next->token == Non)
			cmds->next->token = Cmd;
		cmds->token = Pipe;
	}
}

static void token2(t_cmds *cmds, int i)
{
	if (i == 1)
	{
		if (cmds->prev && cmds->prev->token == Non)
			cmds->prev->token = Cmd;
		if (cmds->next && cmds->next->token == Non)
			cmds->next->token = AppendFile;
		cmds->token = Append;
	}
	else if (i == 2)
	{
		if (cmds->prev && cmds->prev->token == Non)
			cmds->prev->token = Cmd;
		if (cmds->next && cmds->next->token == Non)
			cmds->next->token = HereDocDel;
		cmds->token = HereDoc;
	}
}

void    init_tokens(t_cmds *cmds, int size, t_cmds *lst)
{
	while (cmds)
	{
		size = ft_strlen(cmds->cmd[0]);
		if (size == 1 && cmds->cmd[0][0] == '<')
		{
			token1(cmds, '<');
			cmds = cmds->next;
		}
		else if (size == 1 && cmds->cmd[0][0] == '>')
		{
			token1(cmds, '>');
			cmds = cmds->next;
		}
		else if (size == 1 && cmds->cmd[0][0] == '|')
			token1(cmds, '|');
		else if (size == 2 && cmds->cmd[0][0] == '>' && cmds->cmd[0][1] == '>')
			token2(cmds, 1);
		else if (size == 2 && cmds->cmd[0][0] == '<' && cmds->cmd[0][1] == '<')
			token2(cmds, 2);
		else if (!cmds->prev && !cmds->next)
			cmds->token = Cmd;
		if (cmds)
			cmds = cmds->next;
	}
	non_token(lst);
}

void	non_token(t_cmds *lst)
{
	while (lst)
	{
		if (!lst->cmd[0])
			lst->token = Non;
		else if (is_spaces(lst->cmd[0]) == 0)
			lst->token = Non;
		if (lst->token == Input ||
				lst->token == Output ||
				lst->token == Append ||
				lst->token == HereDoc ||
				lst->token == Pipe)
			lst->operation = Operation;
		else
			lst->operation = NonOperation;
		lst = lst->next;
	}
}

int is_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (1);
		str++;
	}
	return (0);
}
