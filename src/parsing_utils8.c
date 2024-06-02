/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:26:19 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 14:22:08 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_vars(char *s1)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s1 && *s1)
	{
		if (*s1 == '$' && ft_isalpha(s1[1]) == 1)
        {
            s1++;
			if (*s1 != '$')
            {
                while (*s1 && ft_isalpha(s1[0]) == 1)
			    {
                    s1++;
                }
			    in_word = 0;
            }
        }
		else if (in_word == 0)
		{
		    count++;
            while (*s1 && (*s1 != '$' || (ft_isalnum(s1[0]) == 1) || !s1[1]))
		    {
				if (s1[0] == '$' && s1[1] == '$')
					s1++;
                s1++;
            }
		    in_word = 1;
		}
        else
    		s1++;
	}
	return (count);
}

int	dollar_is_in(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
			k++;
		i++;
	}
	return (k);
}

t_command	*command_new(t_command *lst)
{
	t_command	*n_node;
	t_command	*last_node;

	n_node = (t_command *)malloc(sizeof(struct s_command));
	if (n_node == NULL)
		return (NULL);
	n_node->appendfile = NULL;
	n_node->cmd = NULL;
	n_node->heredocdel = NULL;
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

void	print_array(char **str)
{
	printf(":");
	while (str && *str)
	{
		printf("%s-", *str);
		str++;
	}
	printf(":");
}

void	printlist(void *tmp)
{
	t_slist *list;

	list = tmp;
	while (list)
	{
		print_array(list->cmd);
		list = list->next;
	}
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
			if (lst->token == Cmd)
				command->cmd = array_copy(lst->cmd);
			else if (lst->token == Infile)
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
			else if (lst->token == OutFile)
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
			else if (lst->token == AppendFile)
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
			else if (lst->token == HereDocDel)
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
			print_array(tmp->cmd);
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
