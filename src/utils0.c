/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/08 16:59:03 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	count_nodes(t_env *list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	get_cmd_size(t_cmds *list)
{
	int	size;
	int	i;

	size = 0;
	while (list)
	{
		if (list->token == Pipe)
			break ;
		else if (list->token == Cmd && list->cmd)
		{
			i = 0;
			while (list->cmd[i++])
				size++;
		}
		else if (list->cmd[0])
		{
			i = 1;
			while (list->cmd[i++])
				size++;
		}
		list = list->next;
	}
	return (size);
}

t_cmds	*find_cmd(t_cmds *list)
{
	while (list)
	{
		if (list->token == Pipe)
			break ;
		if (list->token == Cmd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	get_command_done(t_cmds *list, t_cmds *head, char **command, bool flag)
{
	int	i;
	int	j;

	list = find_cmd(list);
	i = 0;
	while (list && list->cmd[i])
	{
		command[i] = ft_strdup(list->cmd[i]);
		i++;
	}
	command[i] = NULL;
	while (head)
	{
		if (head->token == Pipe)
			break ;
		else if (head->token == Cmd && flag == true)
			flag = false;
		else
		{
			if (head->token == Cmd)
				command[i++] = ft_strdup(head->cmd[0]);
			j = 1;
			while (head->cmd[0] && head->cmd[j])
				command[i++] = ft_strdup(head->cmd[j++]);
		}
		head = head->next;
	}
	printf("%d \n", i);
}
