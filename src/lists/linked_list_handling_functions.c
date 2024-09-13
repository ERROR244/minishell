/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 09:54:14 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmds	*lstnew(char *cmd, t_cmds *lst, char **str)
{
	t_cmds	*n_node;
	t_cmds	*last_node;

	n_node = (t_cmds *)ft_malloc(sizeof(struct s_cmds), g_signal.node);
	if (n_node == NULL)
		return (NULL);
	if (cmd)
		n_node->cmd = ft_split(cmd, ' ');
	else
		n_node->cmd = str;
	n_node->token = Non;
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

void	slist_clear(t_slist **lst)
{
	t_slist	*curr1;
	t_slist	*curr2;

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

void	lst_env_clear(t_env **lst)
{
	t_env	*curr1;
	t_env	*curr2;

	if (lst == NULL || *lst == NULL)
		return ;
	curr1 = *lst;
	while (curr1->next != NULL)
	{
		curr2 = curr1->next;
		free(curr1->var_name);
		free(curr1);
		curr1 = curr2;
	}
	free(curr1->var_name);
	free(curr1);
	*lst = NULL;
}

t_command	*command_new(t_command *lst)
{
	t_command	*n_node;
	t_command	*last_node;

	n_node = (t_command *)ft_malloc(sizeof(struct s_command), g_signal.node);
	if (n_node == NULL)
		return (NULL);
	n_node->cmd = NULL;
	n_node->infile = NULL;
	n_node->outfile = NULL;
	n_node->next = NULL;
	if (lst == NULL)
	{
		n_node->prev = NULL;
	}
	else
	{
		last_node = command_last(lst);
		n_node->prev = last_node;
	}
	return (n_node);
}
