/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:12:43 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/05 06:52:52 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_list(char **cmd, int size, t_cmds **lst)
{
	t_cmds *node;
	t_cmds *curr;
	int i;
	
	i = 1;
	*lst = lstnew(cmd[0], *lst);
	while (i < size)
	{
		if (i + 2 < size && cmd[i][0] == '|' && cmd[i + 1][0] == '|' && cmd[i + 2][0] == '|')
		{
			if (i + 4 < size && cmd[i + 3][0] == '|')
            	ft_putstr_fd("minishel: syntax error near unexpected token `||'\n", 2);
			else
            	ft_putstr_fd("minishel: syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		node = lstnew(cmd[i], *lst);
		curr = lstlast(*lst);
		curr->next = node;
		i++;
	}
	return (0);
}

char *rm_spaces(char *str)
{
	int i;
	int k;
	int l;
	char *ptr;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	l = i;
    k = i;
	while (str[i++])
        l++;
    i--;
    while (--i != 0 && (str[i] == ' ' || str[i] == '	'))
	{
        l--;
	}
	ptr = malloc(sizeof(char) * (l - k + 1));
    i = 0;
	while (k < l)
		ptr[i++] = str[k++];
	ptr[i] = '\0';
	free(str);
	return (ptr);
}

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

void    init_tokens(t_cmds *cmds, int size)
{
	while (cmds)
	{
		size = ft_strlen(cmds->cmd);
		if (size == 1 && cmds->cmd[0] == '<')
		{
			token1(cmds, '<');
			cmds = cmds->next;
		}
		else if (size == 1 && cmds->cmd[0] == '>')
		{
			token1(cmds, '>');
			cmds = cmds->next;
		}
		else if (size == 1 && cmds->cmd[0] == '|')
			token1(cmds, '|');
		else if (size == 2 && cmds->cmd[0] == '>' && cmds->cmd[1] == '>')
			token2(cmds, 1);
		else if (size == 2 && cmds->cmd[0] == '<' && cmds->cmd[1] == '<')
			token2(cmds, 2);
		else if (!cmds->prev && !cmds->next)
			cmds->token = Cmd;
		if (cmds)
			cmds = cmds->next;
	}
}
