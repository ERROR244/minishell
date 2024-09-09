/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/05 22:36:56 by ksohail-         ###   ########.fr       */
=======
/*   Updated: 2024/07/13 09:12:11 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD
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
=======
t_cmds	*last_update_in_the_list(t_cmds *head, t_cmds *list,
		t_cmds *new_head_tmp, char **command)
{
	t_cmds	*new_head;

	while (head)
	{
		list = head;
		if (get_cmd_size(list) == 0)
			command = get_name("");
		else
		{
			command = malloc(sizeof(char *) * (get_cmd_size(list) + 1));
			get_command_done(list, list, command, true);
		}
		new_head = copy_list(list, command, 0);
		if (new_head_tmp)
			new_head = merge_lists(new_head_tmp, new_head);
		while (list && list->token != Pipe)
			list = list->next;
		new_head_tmp = new_head;
		if (!list)
			break ;
		head = list->next;
	}
	while (new_head->prev)
		new_head = new_head->prev;
	return (new_head);
}

char	**get_cmds_done(t_data *data, char **cmds)
{
	data->line = check_expand(data->line, data);
	cmds = ft_split_msh(data->line);
	return (cmds);
}

void	parsing(t_data *data, t_cmds *lst, t_command *commands, int i)
{
	data->cmds = get_cmds_done(data, data->cmds);
	while (data->cmds[++i])
	{
		if (cmdcheck(data->cmds[i]) == 0)
			data->cmds[i] = rm_spaces(data->cmds[i]);
	}
	get_list(data->cmds, i, &lst, data);
	init_tokens(lst, 0, lst);
	data->lst = lst;
	g_signal.ret = errors_managment(data, 0);
	remove_quotes(lst);
	if (g_signal.ret == 0 && g_signal.sig != -1)
	{
		lst = last_update_in_the_list(lst, lst, NULL, NULL);
		lstclear(&data->lst);
		data->lst = lst;
		commands = get_commands(lst);
		data->lst = lst;
		data->list = commands;
		g_signal.ret = executing(data);
		commands_clear(&commands);
		ft_clear(data);
	}
	else
		ft_clear(data);
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
}
