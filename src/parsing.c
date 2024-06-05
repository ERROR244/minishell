/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/05 18:24:39 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	last_update_in_the_list(t_cmds *list)
{
	t_cmds	*head;
	char	**command;
	char	**ptr = NULL;
	char	**name = NULL;
	char	**str;
	bool	flag = true;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = 0;
	head = list;
	while (list)
	{
		if (list->token == Cmd)
		{
			str = list->cmd;
			i = 0;
			while (str[i])
			{
				size++;
				i++;
			}
		}
		else
		{
			i = 1;
			while (list->cmd[i])
			{
				size++;
				i++;
			}
		}
		list = list->next;
	}
	command = malloc(sizeof(char *) * (size + 1));
	printf("%d \n", size);
	list = head;

	while (list)
	{
		if (list->token == Cmd)
		{
			ptr = list->cmd;
			break;
		}
		list = list->next;
	}
	list = head;
	i = 0;
	while (ptr[i])
	{
		command[i] = ft_strdup(ptr[i]);
		i++;
	}
	while (list)
	{
		if (list->token == Cmd && flag == true)
		{
			flag = false;
			list = list->next;
		}
		else
		{
			str = list->cmd;
			if (list->token == Cmd)
				command[i++] = ft_strdup(str[0]);
			j = 1;
			while (str[j])
			{
				command[i] = ft_strdup(str[j]);
				i++;
				j++;
			}
			list = list->next;
		}
	}
	command[i] = NULL;
	list = head;
	falg = true;
	while (list)
	{
		if (list->token == Cmd && flag == true)
		{
			free_array(list->cmd);
			list->cmd = command;
			flag = false;
			list = list->next;
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
				name = malloc(sizeof(char *) * 2);
				name[0] = list->cmd[0];
				name[1] = NULL;
				free_array(list->cmd);
				list->cmd = name;
			}
			list = list->next;
		}
	}
	

	// for (int i = 0; command[i]; i++)
	// 	printf("%s \n", command[i]);
	// free_array(command);
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

char Gstr[100][100] = { "Cmd", "AppendFile",						//
							"HereDocDel", "Infile",					//
							"OutFile", "Operation",					//
							"NonOperation", "Input",				//
							"Output", "Append",						//
							"HereDoc", "Pipe", 						//
							"Non" };		   						//

int parsing(t_data *data)
{
    t_cmds *lst;
	char **cmds;
	int ret;
	int i;

	i = -1;
	lst = NULL;

	// data->line = check_line(data->line);
	cmds = ft_split_msh(data->line);
	while (cmds[++i])
	{
		if (cmdcheck(cmds[i]) == 0)
			cmds[i] = rm_spaces(cmds[i]);
	}
	get_list(cmds, i, &lst, data);
	remove_quotes(lst);
	init_tokens(lst, 0, lst);

	//
	char **tmp1;								   						//
    t_cmds *tmp2 = lst;							   						//
	while (tmp2)								   						//
	{											   						//
		tmp1 = tmp2->cmd;						   						//
		for (int i = 0; tmp1[i]; i++)			   						//
		{										   						//
			if (data->line[0] != '\0')			   						//
				printf(":%s:", tmp1[i]);		   						//
		} 										   						//
		printf("%s:%s:\n", Gstr[tmp2->token], Gstr[tmp2->operation]);	//
		tmp2 = tmp2->next;												//
	}																	//
	//
	
	last_update_in_the_list(lst);

	//
	char **tmp1;								   						//
    t_cmds *tmp2 = lst;							   						//
	while (tmp2)								   						//
	{											   						//
		tmp1 = tmp2->cmd;						   						//
		for (int i = 0; tmp1[i]; i++)			   						//
		{										   						//
			if (data->line[0] != '\0')			   						//
				printf(":%s:", tmp1[i]);		   						//
		} 										   						//
		printf("%s:%s:\n", Gstr[tmp2->token], Gstr[tmp2->operation]);	//
		tmp2 = tmp2->next;												//
	}																	//
	//
	
	data->lst = lst;
	data->cmds = cmds;
	ret = errors_managment(data, 0);
	// if (ret == 0 || 1)
	// {
	// 	t_command *commands;
	// 	commands = get_commands(lst);
	// 	data->list = commands;
	// 	executing(data);					// exe
	// 	ft_clear(data);
	// 	commands_clear(&commands);
	// }
	// else
		ft_clear(data);
	return (ret);
}
