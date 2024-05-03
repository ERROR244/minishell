/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/03 20:00:40 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmds	*lstnew(char *cmd, t_cmds *lst)
{
	t_cmds	*n_node;
	t_cmds	*last_node;

	n_node = (t_cmds *)malloc(sizeof(struct s_cmds));
	if (n_node == NULL)
		return (NULL);
	n_node->cmd = cmd;
	n_node->next = NULL;
	if (lst == NULL)
	{
		n_node->prev = NULL;
	}
	else
	{
		last_node = lstlast(lst);
		n_node->prev = last_node;
	}
	return (n_node);
}

void	lstclear(t_cmds **lst)
{
	t_cmds	*curr1;
	t_cmds	*curr2;

	if (lst == NULL || *lst == NULL)
		return ;
	curr1 = *lst;
	while (curr1->next != NULL)
	{
		curr2 = curr1->next;
		free(curr1);
		curr1 = curr2;
	}
	free(curr1);
	*lst = NULL;
}

t_cmds	*lstlast(t_cmds *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
