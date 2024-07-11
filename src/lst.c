/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/11 19:01:01 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	commands_clear(t_command **lst)
{
	t_command	*curr1;
	t_command	*curr2;

	if (lst == NULL || *lst == NULL)
		return ;
	curr1 = *lst;
	while (curr1->next != NULL)
	{
		curr2 = curr1->next;
		free_array(curr1->cmd);
		slist_clear(&curr1->infile);
		slist_clear(&curr1->outfile);
		free(curr1);
		curr1 = curr2;
	}
	free_array(curr1->cmd);
	slist_clear(&curr1->infile);
	slist_clear(&curr1->outfile);
	free(curr1);
	*lst = NULL;
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
		free_array(curr1->cmd);
		free(curr1);
		curr1 = curr2;
	}
	free_array(curr1->cmd);
	free(curr1);
	*lst = NULL;
}

t_cmds	*lstlast(t_cmds *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_command	*command_last(t_command *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_slist	*nodes_last(t_slist *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
