/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 09:04:51 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t get_size(char *str)
{
	size_t	k;
	size_t	i;
	char	tmp;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i];
			i++;
			while (str[i] != tmp)
				i++;
			k += 2;
		}
		i++;
	}
	return (i - k);
}

char	*get_string(char *str, size_t i, size_t k, size_t size)
{
	char	*ptr;
	char	tmp;

	if (size == ft_strlen(str))
		return (str);
	ptr = malloc(sizeof(char) * (size + 1));
	while (k < size)
	{
		while (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i++];
			while (str[i] != tmp)
			{
				ptr[k++] = str[i++];
			}
			i++;
		}
		if (k == size)
			break ;
		ptr[k++] = str[i++];
	}
	ptr[k] = '\0';
	free(str);
	return (ptr);
}

void	remove_quotes(t_cmds *lst)
{
	int i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			if (lst->cmd[i] != NULL)
				lst->cmd[i] = get_string(lst->cmd[i], 0, 0, get_size(lst->cmd[i]));
			i++;
		}
		lst = lst->next;
	}
}

t_command	*command_new(t_command *lst)
{
	t_command	*n_node;
	t_command	*last_node;

	n_node = (t_command *)malloc(sizeof(struct s_command));
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

t_command	*get_command(t_cmds *lst)
{
	t_command *command;
	t_command *node;
	t_command *curr;

	command = NULL;
	command = command_new(command);
	while (lst)
	{
		if (lst->token == Pipe)
		{
			node = command_new(command);
			curr = command_last(command);
			curr->next = node;
		}
		lst = lst->next;
	}
	return (command);
}
