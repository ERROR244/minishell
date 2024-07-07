/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 17:38:46 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_list_done(t_cmds *list, char **command, bool flag, char **name)
{
	t_cmds	*head;

	head = list;
	while (list)
	{
		if (list->token == Pipe)
			break ;
		else if ((list->token == Cmd || list->token == Non) && flag == true)
		{
			free_array(list->cmd);
			list->cmd = command;
			flag = false;
		}
		else
		{
			if (list->token == Cmd)
			{
				free_array(list->cmd);
				list->cmd = NULL;
			}
			else
			{
				name = get_name(list->cmd[0]);
				free_array(list->cmd);
				list->cmd = NULL;
				list->cmd = name;
			}
		}
		if (!list->next)
			break ;
		list = list->next;
	}
	if (flag == true)
	{
		list->next = lstnew(NULL, head, command);
		list = list->next;
		list->data = head->data;
	}
}

void	last_update_in_the_list(t_cmds *list)
{
	t_cmds	*head;
	char	**command;
	int		size;

	head = list;
	command = NULL;
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
		get_list_done(list, command, true, NULL);
		while (list && list->token != Pipe)
			list = list->next;
		if (!list)
			break ;
		head = list->next;
	}
}

void	parsing(t_data *data)
{
	// t_command	*commands;
	t_cmds		*lst;
	// char		**cmds;
	int			i;

	i = -1;
	lst = NULL;
	data->flag = true;
	data->line = check_tabs(data->line, 0, 0, data);
	printf("%s \n", data->line);
	// cmds = ft_split_msh(data->line);
	// while (cmds[++i])
	// {
	// 	if (cmdcheck(cmds[i]) == 0)
	// 		cmds[i] = rm_spaces(cmds[i]);
	// }
	// get_list(cmds, i, &lst, data);
	// init_tokens(lst, 0, lst);
	// data->lst = lst;
	// data->cmds = cmds;
	// g_signal.ret = errors_managment(data, 0);
	// data->lst = lst;
	// remove_quotes(lst);
	// if (g_signal.ret == 0 && g_signal.sig != -1)
	// {
	// 	last_update_in_the_list(lst);
	// 	commands = get_commands(lst);
	// 	data->list = commands;
	// 	g_signal.ret = executing(data);
	// 	commands_clear(&commands);
	// 	ft_clear(data);
	// }
	// else
	// 	ft_clear(data);
}
