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

#include "minishell.h"

size_t	get_size(char *str)
{
	size_t	k;
	size_t	i;
	char	tmp;

	i = 0;
	k = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] && str[i + 1] != '\'')
			|| (str[i] == '\"' && str[i + 1] && str[i + 1] != '\"'))
		{
			tmp = str[i];
			i++;
			while (str[i] && str[i + 1] && str[i] != tmp)
				i++;
			k += 2;
		}
		else if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '\"' && str[i + 1] == '\"'))
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
		while ((s[i] == '\'' && s[i + 1] && s[i + 1] != '\'')
			|| (s[i] == '\"' && s[i + 1] && s[i + 1] != '\"'))
		{
			tmp = s[i++];
			while (s[i] && s[i + 1] && s[i] != tmp)
				ptr[k++] = s[i++];
			i++;
		}
		if (k == size)
			break ;
		if ((s[i] == '\'' && s[i + 1] == '\'')
			|| (s[i] == '\"' && s[i + 1] == '\"'))
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

t_command	*get_commands(t_cmds *lst)
{
	t_command	*command;
	t_command	*head;
	t_slist		*infile;
	t_slist		*outfile;

	command = get_command(lst);
	head = command;
	while (command && lst)
	{
		infile = NULL;
		outfile = NULL;
		while (lst && lst->token != Pipe)
		{
			fill_in_commands(&lst, &command, &infile, &outfile);
			lst = lst->next;
		}
		command->infile = get_head(infile);
		command->outfile = get_head(outfile);
		if (lst)
			lst = lst->next;
		command = command->next;
	}
	command = head;
	return (command);
}
