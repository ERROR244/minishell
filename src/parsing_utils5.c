/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 12:05:44 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	get_size(char *str)
{
	size_t	k;
	size_t	i;
	char	tmp;

	i = 0;
	k = 0;
	while (str[i])
	{
		if ((str[i] == 39 && str[i + 1] && str[i + 1] != 39)
			|| (str[i] == 34 && str[i + 1] && str[i + 1] != 34))
		{
			tmp = str[i];
			i++;
			while (str[i] && str[i + 1] && str[i] != tmp)
				i++;
			k += 2;
		}
		else if ((str[i] == 39 && str[i + 1] == 39)
			|| (str[i] == 34 && str[i + 1] == 34))
			i++;
		i++;
	}
	return (i - k);
}

char	*get_string(char *s, size_t i, size_t k, size_t size)
{
	char	*ptr;
	char	tmp;

	ptr = malloc(sizeof(char) * (size + 1));
	while (k < size)
	{
		while ((s[i] == 39 && s[i + 1] && s[i + 1] != 39)
			|| (s[i] == 34 && s[i + 1] && s[i + 1] != 34))
		{
			tmp = s[i++];
			while (s[i] && s[i + 1] && s[i] != tmp)
				ptr[k++] = s[i++];
			i++;
		}
		if (k == size)
			break ;
		if ((s[i] == 39 && s[i + 1] == 39)
			|| (s[i] == 34 && s[i + 1] == 34))
			ptr[k++] = s[i++];
		ptr[k++] = s[i++];
	}
	ptr[k] = '\0';
	free(s);
	return (ptr);
}

void	remove_quotes(t_cmds *lst)
{
	int		i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			if (lst->cmd[i] != NULL
				&& get_size(lst->cmd[i]) != ft_strlen(lst->cmd[i]))
			{
				lst->cmd[i] = get_string(lst->cmd[i], 0, 0,
						get_size(lst->cmd[i]));
			}
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
	t_command	*command;
	t_command	*node;
	t_command	*curr;

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
