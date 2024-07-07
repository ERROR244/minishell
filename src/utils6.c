/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 10:04:43 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_name(char *str)
{
	char	**name;

	name = malloc(sizeof(char *) * 2);
	name[0] = ft_strdup(str);
	name[1] = NULL;
	return (name);
}

char	*get_cmd(char *cmd)
{
	char	*tmp;
	int		i;
	int		k;

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

t_cmds	*lstnew(char *cmd, t_cmds *lst, char **str)
{
	t_cmds	*n_node;
	t_cmds	*last_node;

	n_node = (t_cmds *)malloc(sizeof(struct s_cmds));
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

void	senv_clear(t_env **lst)
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
