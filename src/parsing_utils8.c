/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:26:19 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/05 20:22:33 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_slist	*node_new(t_slist *lst, char **str, t_token token)
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
    t_slist 	*appendfile;
    t_slist 	*heredocdel;
	
	command = get_command(lst);
	tmp = command;
	while (command && lst)
	{
		infile = NULL;
    	outfile = NULL;;
    	appendfile = NULL;
    	heredocdel = NULL;

		while (lst && lst->token != Pipe)
		{
			if (lst->cmd && (lst->token == Cmd || lst->token == Non))
			{
				// if (!command->cmd)
					command->cmd = array_copy(lst->cmd);
				// else
				// {
				// 	if (!infile)
				// 	{
				// 		infile = node_new(infile, lst->cmd, lst->token);
				// 	}
				// 	else
				// 	{
				// 		infile->next = node_new(infile, lst->cmd, lst->token);
				// 		infile = infile->next;
				// 	}
				// }
					
			}
			else if (lst->cmd && lst->token == Infile)
			{
				if (!infile)
				{
					infile = node_new(infile, lst->cmd, lst->token);
				}
				else
				{
					infile->next = node_new(infile, lst->cmd, lst->token);
					infile = infile->next;
				}
			}
			else if (lst->cmd && lst->token == OutFile)
			{
				if (!outfile)
				{
					outfile = node_new(outfile, lst->cmd, lst->token);
				}
				else
				{
					outfile->next = node_new(outfile, lst->cmd, lst->token);
					outfile = outfile->next;
				}
			}
			else if (lst->cmd && lst->token == AppendFile)
			{
				if (!appendfile)
				{
					appendfile = node_new(appendfile, lst->cmd, lst->token);
				}
				else
				{
					appendfile->next = node_new(appendfile, lst->cmd, lst->token);
					appendfile = appendfile->next;
				}
			}
			else if (lst->cmd && lst->token == HereDocDel)
			{
				if (!heredocdel)
				{
					heredocdel = node_new(heredocdel, lst->cmd, lst->token);
				}
				else
				{
					heredocdel->next = node_new(heredocdel, lst->cmd, lst->token);
					heredocdel = heredocdel->next;
				}
			}
			lst = lst->next;
		}
		command->infile = get_head(infile);
		command->outfile = get_head(outfile);
		command->appendfile = get_head(appendfile);
		command->heredocdel = get_head(heredocdel);
		if (lst)
			lst = lst->next;
		command = command->next;
	}
	
	command = tmp;
	
	while (tmp)
	{
		printf("---\n");
		if (tmp->cmd)
		{
			printf("cmd->");
			print_array(tmp->cmd);
		}
		if (tmp->infile)
		{
			printf("\ninfile->          ");
			printlist(tmp->infile);
		}
		if (tmp->outfile)
		{
			printf("\noutfile->         ");
			printlist(tmp->outfile);
		}
		if (tmp->appendfile)
		{
			printf("\nappendfile->      ");
			printlist(tmp->appendfile);
		}
		if (tmp->heredocdel)
		{
			printf("\nheredocdel->      ");
			printlist(tmp->heredocdel);
		}
		printf("\n---\n");
		tmp = tmp->next;
	}
	return (command);
}
