/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:47:27 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/10 12:28:43 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*grep_variable_name(char *line)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	if (!line)
		return (NULL);
	j = ++i;
	while (line[i] && ft_isalnum(line[i]) == 1)
		i++;
	k = i - j;
	str = malloc(sizeof(char) * (k + 1));
	if (!str)
		return (NULL);
	while (l < k)
		str[l++] = line[j++];
	str[l] = '\0';
	return (str);
}

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
            while (*s1 && (*s1 != '$' || ft_isalnum(s1[0]) == 1 || !s1[1]))
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
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				i += 2;
				while (str[i] == ' ')
					i++;
				while (str[i] && ft_isalpha(str[i]) != 1)
					i++;
			}
		}
		if (!str[i])
			break ;
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
