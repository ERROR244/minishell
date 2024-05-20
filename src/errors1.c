/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/20 11:23:13 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_put2str_fd(char *s1, char *s2, int fd)
{
	if (fd >= 0 && s1 && s2)
	{
		while (*s1)
		{
			ft_putchar_fd(*s1, fd);
			s1++;
		}
        while (*s2)
		{
			ft_putchar_fd(*s2, fd);
			s2++;
		}
	}
}

int  errormsg(char *str)
{
    ft_put2str_fd("minishel: syntax error near unexpected token", str, 2);
    return (1);
}

int errors_managment(t_data *data, int i)
{
	t_cmds *curr;

	curr = data->lst;
	while (curr && i == 0)
	{
		if (curr->token == Pipe)
			i = check_for_pipe(curr);
		else if (curr->token == Output || curr->token == Input)
			i = check_for_in_out_put(curr);
		else if (curr->token == Append || curr->token == HereDoc)
			i = check_for_Append_heredoc(curr);
		else
			i = check_access(curr);
		curr = curr->next;
	}
	return (i);
}

int cmdcheck(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void get_list(char **cmd, int size, t_cmds **lst, t_data *data)
{
	t_cmds *node;
	t_cmds *curr;
	int i;
	
	i = 0;
	*lst = lstnew(cmd[i++], *lst);
	(*lst)->data = data;
	while (i < size)
	{
		node = lstnew(cmd[i], *lst);
		node->data = data;
		curr = lstlast(*lst);
		curr->next = node;
		i++;
	}
}
