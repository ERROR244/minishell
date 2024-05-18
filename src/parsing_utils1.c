/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:12:43 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/18 12:33:12 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int cmdcheck(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void get_list(char **cmd, int size, t_cmds **lst, t_data *data)
{
	t_cmds *node;
	t_cmds *curr;
	int i;
	
	i = 0;
	*lst = lstnew(cmd[i++], *lst);
	(*lst)->data = data;
	while (i < size)
	{
		node = lstnew(cmd[i], *lst);
		node->data = data;
		curr = lstlast(*lst);
		curr->next = node;
		i++;
	}
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

void    init_tokens(t_cmds *cmds, int size, t_cmds *lst)
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
		else if (!cmds->prev && !cmds->next)	//	why did i add this?->don't ever change anything agin, don't you dare!
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
		if (is_spaces(lst->cmd) == 0)
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
