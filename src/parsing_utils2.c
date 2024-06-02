/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:48:23 by error01           #+#    #+#             */
/*   Updated: 2024/06/02 16:18:04 by ksohail-         ###   ########.fr       */
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
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
		else if (cmds->next && cmds->next->next && cmds->next->token == Pipe && cmds->next->next->token == Pipe)
			return (errormsg_v2(cmds->next->cmd[0]));
		else if (cmds->next && cmds->next->operation == Operation)
			return (errormsg_v1(cmds->next->cmd[0]));
		else if (cmds->prev && cmds->prev->token == Non && cmds->prev->prev && cmds->prev->prev->token != Pipe)
			return (errormsg_v1(cmds->cmd[0]));
	}
	else if (cmds->token == Output)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
		else if (cmds->next && cmds->next->next && cmds->next->token == Pipe && cmds->next->next->token == Pipe)
			return (errormsg_v2(cmds->next->cmd[0]));
		else if (cmds->next && cmds->next->operation == Operation)
			return (errormsg_v1(cmds->next->cmd[0]));
		else if (cmds->prev && cmds->prev->token == Non && cmds->prev->prev && cmds->prev->prev->token != Pipe)
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
		else if (cmds->prev && cmds->prev->token == Non && cmds->prev->prev && cmds->prev->prev->token != Pipe)
			return (errormsg_v1(cmds->cmd[0]));
		else if (cmds->next && cmds->next->next && cmds->next->token == Pipe && cmds->next->next->token == Pipe)
			return (errormsg_v2(cmds->next->cmd[0]));
		else if (cmds->next && cmds->next->operation == Operation)
			return (errormsg_v1(cmds->next->cmd[0]));
	}
	else if (cmds->token == HereDoc)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
		else if (cmds->prev && cmds->prev->token == Non && cmds->prev->prev && cmds->prev->prev->token != Pipe)
			return (errormsg_v1(cmds->cmd[0]));
		else if (cmds->next && cmds->next->next && cmds->next->token == Pipe && cmds->next->next->token == Pipe)
			return (errormsg_v2(cmds->next->cmd[0]));
		else if (cmds->next && cmds->next->operation == Operation)
			return (errormsg_v1(cmds->next->cmd[0]));
	}
	return (0);
}
