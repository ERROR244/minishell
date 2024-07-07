/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:26:19 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 09:07:57 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_slist	*node_new(t_slist *lst, char *str, t_token token)
{
	t_slist	*n_node;
	t_slist	*last_node;

	n_node = (t_slist *)malloc(sizeof(struct s_slist));
	if (n_node == NULL)
		return (NULL);
	n_node->cmd = str;
	n_node->token = token;
	n_node->next = NULL;
	if (lst == NULL)
	{
		n_node->prev = NULL;
	}
	else
	{
		last_node = nodes_last(lst);
		n_node->prev = last_node;
	}
	return (n_node);
}

t_slist	*get_head(t_slist *list)
{
	while (list)
	{
		if (!list->prev)
			break;
		list = list->prev;
	}
	return (list);
}


char	**array_copy(char **str)
{
	char	**ptr;
	int i;
	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	ptr = malloc(sizeof(char *) * (i + 1));
	i = 0;

	while (str[i])
	{
		ptr[i] = ft_strdup(str[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

t_command	*get_commands(t_cmds *lst)
{
	t_command	*command;
	t_command	*tmp;
	t_slist  	*infile;
    t_slist 	*outfile;;
	
	command = get_command(lst);
	tmp = command;
	while (command && lst)
	{
		infile = NULL;
    	outfile = NULL;;
		while (lst && lst->token != Pipe)
		{
			if (lst->cmd && (lst->token == Cmd || lst->token == Non))
				command->cmd = array_copy(lst->cmd);
			else if (lst->cmd && lst->token == Infile)
			{
				if (!infile)
					infile = node_new(infile, lst->cmd[0], lst->token);
				else
				{
					infile->next = node_new(infile, lst->cmd[0], lst->token);
					infile = infile->next;
				}
			}
			else if (lst->cmd[0] && (lst->token == OutFile || lst->token == AppendFile))
			{
				
				if (!outfile)
					outfile = node_new(outfile, lst->cmd[0], lst->token);
				else
				{
					outfile->next = node_new(outfile, lst->cmd[0], lst->token);
					outfile = outfile->next;
				}
			}
			lst = lst->next;
		}
		command->infile = get_head(infile);
		command->outfile = get_head(outfile);
		if (lst)
			lst = lst->next;
		command = command->next;
	}
	
	command = tmp;
	return (command);
}
