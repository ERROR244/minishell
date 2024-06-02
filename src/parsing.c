/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 17:34:51 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *check_line(char *str)
{
	char *ptr;
	int i;
	int j;

	i = 0;
	j = 0;
	ptr = str;
	return (ptr);
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
