/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:12:43 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 19:22:36 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void get_list(char **cmd, int size, t_cmds **lst)
{
	t_cmds *node;
	t_cmds *curr;
	int i;
	
	i = 1;
	*lst = lstnew(cmd[0], *lst);
	while (i < size)
	{
		node = lstnew(cmd[i], *lst);
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

void    init_tokens(t_cmds *cmds)
{
	int size;
	
	while (cmds)
	{
		size = ft_strlen(cmds->cmd);
		if (size == 1 && cmds->cmd[0] == '<')
		{
			if (cmds->prev && cmds->prev->token == Non)
				cmds->prev->token = Cmd;
			if (cmds->next && cmds->next->token == Non)
				cmds->next->token = Infile;
			cmds->token = Input;
			cmds = cmds->next;
		}
		else if (size == 1 && cmds->cmd[0] == '>')
		{
			if (cmds->prev && cmds->prev->token == Non)
				cmds->prev->token = Cmd;
			if (cmds->next && cmds->next->token == Non)
				cmds->next->token = OutFile;
			cmds->token = Output;
			cmds = cmds->next;
		}
		else if (size == 1 && cmds->cmd[0] == '|')
		{
			if (cmds->prev && cmds->prev->token == Non)
				cmds->prev->token = Cmd;
			if (cmds->next && cmds->next->token == Non)
				cmds->next->token = Cmd;
			cmds->token = Pipe;
		}
		else if (size == 2 && cmds->cmd[0] == '>' && cmds->cmd[1] == '>')
		{
			if (cmds->prev && cmds->prev->token == Non)
				cmds->prev->token = Cmd;
			if (cmds->next && cmds->next->token == Non)
				cmds->next->token = AppendFile;
			cmds->token = Append;
		}
		else if (size == 2 && cmds->cmd[0] == '<' && cmds->cmd[1] == '<')
		{
			if (cmds->prev && cmds->prev->token == Non)
				cmds->prev->token = Cmd;
			if (cmds->next && cmds->next->token == Non)
				cmds->next->token = HereDocDel;
			cmds->token = HereDoc;
		}
		else if (!cmds->prev && !cmds->next)
			cmds->token = Cmd;
		cmds = cmds->next;
	}
}
