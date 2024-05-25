/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:48:23 by error01           #+#    #+#             */
/*   Updated: 2024/05/25 11:36:47 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void close_used_files(t_data *data)
{
	t_cmds *cmds;

	if (!data)
		return ;
	cmds = data->lst;
	while (cmds)
	{
		if (cmds->token == Infile)
			close(data->infile);
		else if (cmds->token == OutFile)
			close(data->outfile);
		else if (cmds->token == AppendFile)
			close(data->Appfile);
		cmds = cmds->next;
	}
}

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
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
		else if (cmds->prev && cmds->prev->token == Non)
			return (errormsg_v1(cmds->cmd[0]));
	}
	else if (cmds->token == Output)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
		else if (cmds->prev && cmds->prev->token == Non)
			return (errormsg_v1(cmds->cmd[0]));
	}
	return (0);
}

int check_for_Append_heredoc(t_cmds *cmds)
{
	
	if (cmds->token == Append)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
		else if (cmds->prev && cmds->prev->token == Non)
			return (errormsg_v1(cmds->cmd[0]));
	}
	else if (cmds->token == HereDoc)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
		else if (cmds->prev && cmds->prev->token == Non)
			return (errormsg_v1(cmds->cmd[0]));
	}
	return (0);
}

int	check_access(t_cmds *curr)
{
	if (curr->token == Infile)
		return (check_file(curr));
	// else if (curr->token == OutFile)
	// 	curr->data->outfile = open(curr->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	// else if (curr->token == AppendFile)
	// 	curr->data->outfile = open(curr->cmd[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (curr->token == HereDocDel)
		return (check_if_NULL(curr->cmd[0]));
	return (0);
}
