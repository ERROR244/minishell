/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 11:20:28 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*copy_node(char **cmd, t_token token, bool flag)
{
	t_cmds	*new_node;

	new_node = (t_cmds *)ft_malloc(sizeof(t_cmds), g_signal.node);
	if (flag == true)
		new_node->cmd = cmd;
	else
		new_node->cmd = get_name(cmd[0]);
	new_node->token = token;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_cmds	*copy_single_node(t_cmds *curr, int *i)
{
	if (curr->token == Cmd && *i == 0)
	{
		*i = 1;
		return (NULL);
	}
	return (copy_node(curr->cmd, curr->token, false));
}

t_cmds	*add_head_to_new_list(t_cmds *head, t_cmds *new_head)
{
	if (new_head)
	{
		head->next = new_head;
		new_head->prev = head;
	}
	return (head);
}

t_cmds	*copy_list(t_cmds *curr, char **command, int i)
{
	t_cmds	*new_node;
	t_cmds	*head;
	t_cmds	*new_head;
	t_cmds	*new_tail;

	new_tail = NULL;
	new_head = NULL;
	head = copy_node(command, Cmd, true);
	while (curr && curr->token != Pipe)
	{
		if (curr->token != Cmd || i == 0)
		{
			new_node = copy_single_node(curr, &i);
			if (!new_head)
				new_head = new_node;
			else
			{
				new_tail->next = new_node;
				new_node->prev = new_tail;
			}
			new_tail = new_node;
		}
		curr = curr->next;
	}
	return (add_head_to_new_list(head, new_head));
}

t_cmds	*merge_lists(t_cmds *list1, t_cmds *list2)
{
	t_cmds	*current;
	t_cmds	*pipe;

	if (!list1)
		return (list2);
	if (!list2)
		return (list1);
	pipe = copy_node(get_name("|"), Pipe, true);
	current = list1;
	while (current->next)
		current = current->next;
	current->next = pipe;
	pipe->prev = current;
	pipe->next = list2;
	list2->prev = pipe;
	return (list1);
}
