/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/05 22:36:56 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_array(char **array)
{
    char **ptr = array;
    while (*ptr)
	{
        free(*ptr);
        ptr++;
    }
    free(array);
}

int errors_managment(t_data *data, int i)
{
	t_cmds *curr;

	curr = data->lst;
	while (curr && i == 0)
	{
		if (curr->token == AppendFile)
			i = check_file(curr->cmd);
		else if (curr->token == HereDocDel)
			i = check_if_NULL(curr->cmd);
		else if (curr->token == Infile)
			i = check_file(curr->cmd);
		else if (curr->token == OutFile)
			i = check_if_NULL(curr->cmd);
		else if (curr->token == Pipe)
			i = check_for_pipe(curr);
		curr = curr->next;
	}
	return (i);
}

void parsing(t_data *data)
{
    t_cmds *lst;
    t_cmds *cur;
	char **cmds;
	int ret;
	int flag;
	int i;

	i = -1;
	cmds = ft_split_msh(data->line);
	lst = NULL;
	while (cmds[++i])
		cmds[i] = rm_spaces(cmds[i]);

    flag = get_list(cmds, i, &lst);
	init_tokens(lst, 0);
	data->lst = lst;
	data->cmds = cmds;
	ret = errors_managment(data, flag);
	if (ret == 11)
	{
		printf("11\n\n");
		ret = 0;
	}
	if (ret == 0)
	{
		// init_the_tree(lst);
		char str[100][100] = { "Cmd", "AppendFile",
								"HereDocDel", "Infile",
								"OutFile", "Input",
								"Output", "Append",
								"HereDoc", "Pipe",
								"Non" };
		while (lst)
		{
			if (lst->cmd == NULL)
				printf("cmds->cmd == NULL");
			else
				printf("%s---->%s \n", lst->cmd, str[lst->token]);
			if (!lst->next)
				break;
			lst = lst->next;
		}
		
		printf("\n");
		
		while (lst)
		{
			if (!lst->prev)
				break;
			lst = lst->prev;
		}
		// executing(data);	// exe
	}
	cur = lst;		// free
	while (cur)
	{
		free(cur->cmd);
		free(cur->flags);
		cur = cur->next;
	}
	lstclear(&lst);
	free_array(cmds);
}
