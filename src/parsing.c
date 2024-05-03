/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/03 20:00:32 by ksohail-         ###   ########.fr       */
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

char *rm_spaces(char *str)
{
	int i;
	int k;
	int l;
	char *ptr;

	i = 0;
	l = 0;
	k = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	l = i;
    k = i;
	while (str[i++])
        l++;
    i--;
    while (--i != 0 && (str[i] == ' ' || str[i] == '	'))
        l--;
	ptr = malloc(sizeof(char) * (l - k + 1));
    i = 0;
	while (k < l)
		ptr[i++] = str[k++];
	ptr[i] = '\0';
	free(str);
	return (ptr);
}

void get_list(char **cmd, int size, t_cmds **lst)
{
	t_cmds *node;
	t_cmds *curr;
	int i;
	
	i = 1;
	*lst = lstnew(cmd[0], *lst);
	while (i < size)
	{
		node = lstnew(cmd[i], *lst);
		curr = lstlast(*lst);
		curr->next = node;
		i++;
	}
}


void parsing(t_data *data)
{
    t_cmds *lst;
	char **cmds;
	int i;

	i = -1;
	cmds = ft_split(data->line);
	while (cmds[++i])
		cmds[i] = rm_spaces(cmds[i]);

    get_list(cmds, i, &lst);

	t_cmds *curr = lst;
	while (curr)
	{
		if (curr->cmd == NULL)
			printf("cmds->cmd == NULL");
		else
			printf("%s \n", curr->cmd);
		curr = curr->next;
	}
	lstclear(&lst);
	free_array(cmds);
}
