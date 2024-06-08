/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/08 11:27:33 by ksohail-         ###   ########.fr       */
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
    return (2);
}

int check_quot(char *str)
{
  int i;

  i = 0;
  while (*str)
  {
    if (*str == 34 || *str == 39)
      i++;
    str++;
  }
  return (i);
}

void  open_heredoc(t_cmds *cmds)
{
	static int  i;
	char    	*tmp1;
	char    	*filename;
	char    	*line;
	bool    	flag;
	int     	fd;

	flag = true;
	if (check_quot(cmds->cmd[0]) != 0)
		flag = false;
	tmp1 = ft_itoa(i);
	filename = ft_strjoin("/tmp/HereDoc", tmp1);
	free(tmp1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, cmds->cmd[0]) == 0)
			break;
		if (flag == true)
			line = expand_variable(line, cmds->data);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	close(fd);
	free_array(cmds->cmd);
	cmds->cmd = malloc(sizeof(char *) * 2);
	cmds->cmd[0] = filename;
	cmds->cmd[1] = NULL;
	cmds->prev->token = Input;
	cmds->token = Infile;
	i++;
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
		else if (curr->token == HereDocDel)
			open_heredoc(curr);
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
