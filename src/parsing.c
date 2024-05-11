/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/12 00:02:26 by error01          ###   ########.fr       */
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

int check_for_in_out_put(t_cmds *cmds)
{
	
	if (cmds->token == Input)
	{
		if (!cmds->next)
			return (errormsg(" 'newline'\n"));
	}
	else if (cmds->token == Output)
	{
		if (!cmds->next)
			return (errormsg(" 'newline'\n"));
	}
	return (0);
}

int errors_managment(t_data *data, int i)
{
	t_cmds *curr;

	curr = data->lst;
	while (curr && i == 0)
	{
		// if (curr->token == AppendFile)
		// 	i = check_file(curr->cmd);
		if (curr->token == HereDocDel)
			i = check_if_NULL(curr->cmd);
		else if (curr->token == Infile)
			i = check_file(curr->cmd);
		else if (curr->token == OutFile)
			i = check_if_NULL(curr->cmd);
		else if (curr->token == Pipe)
			i = check_for_pipe(curr);
		else if (curr->token == Output || curr->token == Input)
			i = check_for_in_out_put(curr);
		else if (curr->token == Append || curr->token == HereDoc)
			i = check_for_file_access(curr);		//	to do
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
	{
		if (cmdcheck(cmds[i]) == 0)
			cmds[i] = rm_spaces(cmds[i]);
	}
	
	
	// for (int i = 0; cmds[i]; i++)
	// 	printf(":%s:\n", cmds[i]);
    
	
	flag = get_list(cmds, i, &lst);
	init_tokens(lst, 0);
	data->lst = lst;
	data->cmds = cmds;
	ret = errors_managment(data, flag);

	
	// if (ret == 11)
	// {
	// 	printf("11\n\n");
	// 	ret = 0;
	// }
	// if (ret == 0)
	// {
	// 	// init_the_tree(lst);
	// 	char str[100][100] = { "Cmd", "AppendFile",
	// 							"HereDocDel", "Infile",
	// 							"OutFile", "Input",
	// 							"Output", "Append",
	// 							"HereDoc", "Pipe",
	// 							"Non" };
	// 	while (lst)
	// 	{
	// 		if (lst->cmd == NULL)
	// 			printf("cmds->cmd == NULL");
	// 		else
	// 			printf("%s---->%s \n", lst->cmd, str[lst->token]);
	// 		if (!lst->next)
	// 			break;
	// 		lst = lst->next;
	// 	}
		
	// 	printf("\n");
		
	// 	while (lst)
	// 	{
	// 		if (!lst->prev)
	// 			break;
	// 		lst = lst->prev;
	// 	}
	// 	// executing(data);	// exe
	// }
	
	
	ret++;
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
