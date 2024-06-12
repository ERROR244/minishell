/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/12 00:47:43 by ksohail-         ###   ########.fr       */
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

int	ft_strcmp_for_heredoc(char *s1, char *s2)
{
	char *str;
	int k;
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = get_string(ft_strdup(s2), 0, 0, get_size(s2));
	// printf("%s \n", str);
	while (s1[i] == str[i] && s1[i] != '\0' && str[i] != '\0')
		i++;
	k = s1[i] - str[i];
	free(str);
	return (k);
}

void  open_heredoc(t_cmds *cmds)
{
	static int  i;
	static int	k;
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
	my_signal.flag_heredoc = true;
	while (my_signal.flag_heredoc == true)
	{
		k++;
		line = readline(">");
		if (my_signal.flag_heredoc == false)
			break ;
		if (!line)
		{
			char *num = ft_itoa(k);
			ft_putstr_fd("minishell: warning: here-document at line ", 2);
			ft_putstr_fd(num, 2);
			free(num);
			ft_putstr_fd("  delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(cmds->cmd[0], 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		else if (ft_strcmp_for_heredoc(line, cmds->cmd[0]) == 0)
			break;
		if (flag == true)
			line = expand_variable(line, cmds->data);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	close(fd);
	my_signal.flag_heredoc = false;
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
	t_cmds *head;

	curr = data->lst;
	head = curr;
	while (curr && i == 0)
	{
		if (curr->token == Pipe)
			i = check_for_pipe(curr);
		else if (curr->token == Output || curr->token == Input)
			i = check_for_in_out_put(curr);
		else if (curr->token == Append || curr->token == HereDoc)
			i = check_for_Append_heredoc(curr);
		curr = curr->next;
	}
	while (head)
	{
		if (head->token == HereDocDel)
			open_heredoc(head);
		head = head->next;
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
