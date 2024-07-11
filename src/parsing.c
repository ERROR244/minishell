/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/11 12:12:34 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_flags(t_cmds **list)
{
	char	**name;

	if ((*list)->token == Cmd)
		free_array((*list)->cmd);
	else
	{
		name = get_name((*list)->cmd[0]);
		free_array((*list)->cmd);
		(*list)->cmd = name;
	}
}

void	get_list_done(t_cmds *head, t_cmds *list, char **command, bool flag)
{
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
		else if (list->token == Cmd || list->token == Non)
			get_flags(&list);
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

// void	get_list(char **cmd, int size, t_cmds **lst, t_data *data)
// {
// 	t_cmds	*node;
// 	t_cmds	*curr;
// 	int		i;

// 	i = 0;
// 	if (cmd[0] == NULL)
// 	{
// 		*lst = lstnew("\n", *lst, NULL);
// 		return ;
// 	}
// 	*lst = lstnew(cmd[i++], *lst, NULL);
// 	(*lst)->data = data;
// 	while (i < size)
// 	{
// 		node = lstnew(cmd[i], *lst, NULL);
// 		node->data = data;
// 		curr = lstlast(*lst);
// 		curr->next = node;
// 		i++;
// 	}
// }

void	last_update_in_the_list(t_cmds *head, t_cmds *list, char **command)
{
	int	size;
	t_cmds *tmp;

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
		get_list_done(list, list, command, true);
		while (list && list->token != Pipe)
			list = list->next;
		if (!list)
			break ;
		head = list->next;
	}
	tmp = head;
	while (tmp)
	{
		if (tmp->token == Cmd)
		{
			printf("Cmd--->	");
			print_array(tmp->cmd);
		}
		else if (tmp->token == Infile)
		{
			printf("infile--->	");
			print_array(tmp->cmd);
		}
		else if (tmp->token == OutFile)
		{
			printf("outfile--->	");
			print_array(tmp->cmd);
		}
		else
			printf("-------------------\n");
		tmp = tmp->next;
	}
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
	t_cmds *tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->token == Cmd)
		{
			printf("Cmd--->	");
			print_array(tmp->cmd);
		}
		else if (tmp->token == Infile)
		{
			printf("infile--->	");
			print_array(tmp->cmd);
		}
		else if (tmp->token == OutFile)
		{
			printf("outfile--->	");
			print_array(tmp->cmd);
		}
		else
			printf("-------------------\n");
		tmp = tmp->next;
	}
	printf("***************************************************\n");
	if (g_signal.ret == 0 && g_signal.sig != -1)
	{
		last_update_in_the_list(lst, lst, NULL);
		tmp = lst;
		while (tmp)
		{
			if (tmp->token == Cmd)
			{
				printf("Cmd--->	");
				print_array(tmp->cmd);
			}
			else if (tmp->token == Infile)
			{
				printf("infile--->	");
				print_array(tmp->cmd);
			}
			else if (tmp->token == OutFile)
			{
				printf("outfile--->	");
				print_array(tmp->cmd);
			}
			else
				printf("-------------------\n");
			tmp = tmp->next;
		}
	// 	commands = get_commands(lst);
	// 	data->list = commands;
	// 	g_signal.ret = executing(data);
	// 	commands_clear(&commands);
	// 	ft_clear(data);
	}
	else
		ft_clear(data);
}
