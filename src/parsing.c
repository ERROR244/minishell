/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/08 15:31:05 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char Gstr[100][100] = { "Cmd", "AppendFile",						//
							"HereDocDel", "Infile",					//
							"OutFile", "Operation",					//
							"NonOperation", "Input",				//
							"Output", "Append",						//
							"HereDoc", "Pipe", 						//
							"Non" };		   						//

int	get_cmd_size(t_cmds *list)
{
	int		size;
	int		i;

	size = 0;
	while (list)
	{
		if (list->token == Pipe)
			break ;
		else if (list->token == Cmd && list->cmd)
		{
			i = 0;
			while (list->cmd[i++])
				size++;
		}
		else if (list->cmd[0])
		{
			i = 1;
			while (list->cmd[i++])
				size++;
		}
		list = list->next;
	}
	return (size);
}

t_cmds	*find_cmd(t_cmds *list)
{
	while (list)
	{
		if (list->token == Pipe)
			break ;
		if (list->token == Cmd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	get_command_done(t_cmds *list, t_cmds *head, char **command, bool flag)
{
	int i;
	int j;

	list = find_cmd(list);
	i = 0;
	while (list && list->cmd[i])
	{
		command[i] = ft_strdup(list->cmd[i]);
		i++;
	}
	while (head)
	{
		if (head->token == Pipe)
			break ;
		else if (head->token == Cmd && flag == true)
			flag = false;
		else
		{
			if (head->token == Cmd)
				command[i++] = ft_strdup(head->cmd[0]);
			j = 1;
			while (head->cmd[0] && head->cmd[j])
				command[i++] = ft_strdup(head->cmd[j++]);
		}
		head = head->next;
	}
	command[i] = NULL;
}

char	**get_name(char *str)
{
	char **name;

	name = malloc(sizeof(char *) * 2);
	name[0] = ft_strdup(str);
	name[1] = NULL;
	return (name);
}

void	get_list_done(t_cmds *list, char **command, bool flag, char **name)
{
	t_cmds *head;

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
	t_cmds	*tmp;
	char	**command;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	head = list;
	tmp = list;
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

void ft_clear(t_data *data)
{
    t_cmds *cur;

	cur = data->lst;
	while (cur)
	{
		free_array(cur->cmd);
		cur = cur->next;
	}
	lstclear(&data->lst);
	free_array(data->cmds);
}

int parsing(t_data *data)
{
	t_command *commands;
    t_cmds *lst;
	char **cmds;
	int ret = 0;
	int i;

	i = -1;
	lst = NULL;
	data->flag = true;
	data->line = check_tabs(data->line, 0, 0, 0, data);
	cmds = ft_split_msh(data->line);
	while (cmds[++i])
	{
		if (cmdcheck(cmds[i]) == 0)
			cmds[i] = rm_spaces(cmds[i]);
	}
	get_list(cmds, i, &lst, data);
	init_tokens(lst, 0, lst);

	// //	
	// char **tmp1;								   							//
    // t_cmds *tmp2 = lst;							  						//
	// while (tmp2)								   							//
	// {											   						//
	// 	tmp1 = tmp2->cmd;						   							//
	// 	for (int i = 0; tmp1[i]; i++)			   							//
	// 	{										   							//
	// 		if (data->line[0] != '\0')			   							//
	// 			printf(":%s:", tmp1[i]);		   							//
	// 	} 										   							//
	// 	printf("%s:%s:\n", Gstr[tmp2->token], Gstr[tmp2->operation]);		//
	// 	tmp2 = tmp2->next;													//
	// }																	//
	// //
	
	data->lst = lst;
	data->cmds = cmds;
	ret = errors_managment(data, 0);
	data->lst = lst;
	remove_quotes(lst);
	if (ret == 0)
	{
		last_update_in_the_list(lst);
		commands = get_commands(lst);
		data->list = commands;
		ret = executing(data);					// exe
		commands_clear(&commands);
		ft_clear(data);
	}
	else
		ft_clear(data);
	return (ret);
}
