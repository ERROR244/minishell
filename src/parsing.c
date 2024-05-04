/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 19:23:34 by ksohail-         ###   ########.fr       */
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

void parsing(t_data *data)
{
    t_cmds *lst;
    t_cmds *cur;
	char **cmds;
	int i;

	i = -1;
	cmds = ft_split_msh(data->line);
	lst = NULL;
	while (cmds[++i])
		cmds[i] = rm_spaces(cmds[i]);

    get_list(cmds, i, &lst);
	init_tokens(lst);
	// errors_managment(lst);

	// init_the_tree(lst);

	// executing(data);	// exe
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
