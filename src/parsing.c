/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/01 15:25:41 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_line(char *str, int i)
{
	char *ptr;
	int j;
	
	j = 0;
	ptr = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		ptr[j] = str[j];
		j++;
	}
	ptr[j] = '\0';
	free(str);
	return (ptr);
}

int chack_if_prev_Non(char *str, int size)
{
	while (str[size])
	{
		while (size != 0 && str[size] == ' ')
			size--;
		if (size)
			return (1);
	}
	return (0);
}

char *check_line(char *str)
{
	char *ptr;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == '|')
		i++;
	while (str[i])
	{
		while (str[i] == '|')
		{
			i++;
			j++;
		}
		if ((j == 2 || !str[i]) && chack_if_prev_Non(str, i) == 0)
			break ;
		j = 0;
		i++;
	}
	if (j != 2)
		return (str);
	ptr = get_line(str, i - j);
	return (ptr);
}

void ft_clear(t_data *data)
{
    t_cmds *cur;

	// close_used_files(data);
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

	data->line = check_line(data->line);
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
	
	data->lst = lst;
	data->cmds = cmds;
	ret = errors_managment(data, 0);
	if (ret == 0 || 1)
	{
		t_command *commands;
		commands = get_commands(lst);
		// ret = executing(data);		// exe
		// executing(data);					// exe_tmp
		ft_clear(data);
		commands_clear(&commands);
	}
	else
		ft_clear(data);
	return (ret);
}

t_command	*command_new(t_command *lst)
{
	t_command	*n_node;
	t_command	*last_node;

	n_node = (t_command *)malloc(sizeof(struct s_command));
	if (n_node == NULL)
		return (NULL);
	n_node->appendfile = NULL;
	n_node->cmd = NULL;
	n_node->heredocdel = NULL;
	n_node->infile = NULL;
	n_node->outfile = NULL;
	n_node->next = NULL;
	if (lst == NULL)
	{
		n_node->prev = NULL;
	}
	else
	{
		last_node = command_last(lst);
		n_node->prev = last_node;
	}
	return (n_node);
}

t_command	*get_command(t_cmds *lst)
{
	t_command *command;
	t_command *node;
	t_command *curr;

	command = NULL;
	command = command_new(command);
	while (lst)
	{
		if (lst->token == Pipe)
		{
			node = command_new(command);
			curr = command_last(command);
			curr->next = node;
		}
		lst = lst->next;
	}
	return (command);
}

t_command	*get_commands(t_cmds *lst)
{
	t_command	*command;
	t_command	*tmp;

	command = get_command(lst);
	tmp = command;
	while (command && lst)
	{
		while (lst && lst->token != Pipe)
		{
			if (lst->token == Cmd)
				command->cmd = lst->cmd;
			else if (lst->token == Infile)
				command->infile = lst;
			else if (lst->token == OutFile)
				command->outfile = lst;
			else if (lst->token == AppendFile)
				command->appendfile = lst;
			else if (lst->token == HereDocDel)
				command->heredocdel = lst;
			lst = lst->next;
		}
		if (lst)
			lst = lst->next;
		command = command->next;
	}



	
	command = tmp;
	while (tmp)
	{
		if (tmp->cmd)
			printf(":%s:", tmp->cmd[0]);
		if (tmp->infile)
			printf(":%s:", tmp->infile->cmd[0]);
		if (tmp->outfile)
			printf(":%s:", tmp->outfile->cmd[0]);
		if (tmp->appendfile)
			printf(":%s:", tmp->appendfile->cmd[0]);
		if (tmp->heredocdel)
			printf(":%s:", tmp->heredocdel->cmd[0]);
		printf("\n");
		tmp = tmp->next;
	}
	return (command);
}
