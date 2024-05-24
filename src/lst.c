/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/24 17:15:02 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_cmd(char *cmd)
{
	char *tmp;
	int i;
	int k;

	i = 0;
	k = 0;
	while (cmd && cmd[i] && cmd[i] != ' ')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	while (k < i)
    {
		tmp[k] = cmd[k];
        k++;
    }
	tmp[k] = '\0';
	return (tmp);
}

t_cmds	*lstnew(char *cmd, t_cmds *lst)
{
	t_cmds	*n_node;
	t_cmds	*last_node;

	n_node = (t_cmds *)malloc(sizeof(struct s_cmds));
	if (n_node == NULL)
		return (NULL);
	n_node->cmd = ft_split(cmd, ' ');
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
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
