/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:48:23 by error01           #+#    #+#             */
/*   Updated: 2024/05/12 01:22:15 by error01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void close_used_files(t_data *data)
{
	t_cmds *cmds;

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