/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/11 19:10:42 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmds *copy_node(char **cmd, t_token token, bool flag)
{
    t_cmds *new_node;
	
	new_node = (t_cmds *)malloc(sizeof(t_cmds));
	if (flag == true)
	    new_node->cmd = array_copy(cmd);
	else
	    new_node->cmd = get_name(cmd[0]);
    new_node->token = token;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

t_cmds *copy_list(t_cmds *lst, char **command)
{
	t_cmds *new_node;
	t_cmds *new_head;
	t_cmds *head;
    t_cmds *new_tail;
    t_cmds *current;
	int i = 0;
	
    if (!lst)
		return (NULL);

    new_tail = NULL;
	new_head = NULL;
    current = lst;
	head = copy_node(command, Cmd, true);
    while (current)
	{
		if (current->token == Pipe)
			break ;
        else if (current->token != Cmd || i == 0)
		{
			if (current->token == Cmd && i == 0)
			{
				i = 1;
            	new_node = head;
			}
			else
            	new_node = copy_node(current->cmd, current->token, false);

            
            if (!new_head)
                new_head = new_node;
            else
			{
                new_tail->next = new_node;
                new_node->prev = new_tail;
            }
			new_tail = new_node;
        }
        current = current->next;
    }
	if (i == 0)
	{
		head->next = new_head;
		new_head->prev = head;
		return (head);
	}
    return (new_head);
}

t_cmds *merge_lists(t_cmds *list1, t_cmds *list2) 
{
    t_cmds *current;
    t_cmds *pipe;

    if (!list1)
		return (list2);
    if (!list2)
		return (list1);

	pipe = copy_node(get_name("|"), Pipe, true);
    current = list1;
    while (current->next) 
        	current = current->next;
    current->next = pipe;
	pipe->prev = current;
	pipe->next = list2;
    list2->prev = pipe;
    return (list1);
}


t_cmds	*last_update_in_the_list(t_cmds *head, t_cmds *list, char **command)
{
	int	size;
	t_cmds *new_head;
	t_cmds *new_head_tmp = NULL;

	while (head)
	{
		list = head;
		size = get_cmd_size(list);
		if (size == 0)
		{
			list->data->flag = false;
			command = malloc(sizeof(char *) * (2));
			command[0] = ft_strdup("");
			command[1] = NULL;
		}
		else
		{
			command = malloc(sizeof(char *) * (size + 1));
			get_command_done(list, list, command, true);
		}
		new_head = copy_list(list, command);
		if (new_head_tmp)
			new_head = merge_lists(new_head_tmp, new_head);
		while (list && list->token != Pipe)
			list = list->next;
		new_head_tmp = new_head;
		if (!list)
			break ;
		head = list->next;
	}
	while (new_head)
	{
		if (!new_head->prev)
			break;
		new_head = new_head->prev;
	}
	return (new_head);
}

char	**get_cmds_done(t_data *data, char **cmds)
{
	data->line = check_tabs(data->line, 0, 0, data);
	cmds = ft_split_msh(data->line);
	return (cmds);
}

void	parsing(t_data *data, t_cmds *lst, char **cmds, int i)
{
	t_command	*commands;

	cmds = get_cmds_done(data, cmds);
	while (cmds[++i])
	{
		if (cmdcheck(cmds[i]) == 0)
			cmds[i] = rm_spaces(cmds[i]);
	}
	get_list(cmds, i, &lst, data);


	init_tokens(lst, 0, lst);
	data->lst = lst;
	data->cmds = cmds;
	g_signal.ret = errors_managment(data, 0);
	remove_quotes(lst);
	if (g_signal.ret == 0 && g_signal.sig != -1)
	{
		lst = last_update_in_the_list(lst, lst, NULL);
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
}
