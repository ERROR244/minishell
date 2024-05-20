/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/20 12:01:17 by ksohail-         ###   ########.fr       */
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

	close_used_files(data);
	cur = data->lst;		// free
	while (cur)
	{
		free(cur->cmd);
		free(cur->flags);
		cur = cur->next;
	}
	lstclear(&data->lst);
	free_array(data->cmds);
}

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
	init_tokens(lst, 0, lst);
	data->lst = lst;
	data->cmds = cmds;
	ret = errors_managment(data, 0);
	if (ret == 0)
		ret = executing(data);		// exe
	else
		return (ret);
	ft_clear(data);
	return (ret);
}
