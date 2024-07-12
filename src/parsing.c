/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 15:42:34 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
}
