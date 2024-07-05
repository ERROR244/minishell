/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/05 01:40:10 by ohassani         ###   ########.fr       */
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

int *fr()
{
	static int i = -1;

	return (&i);
}

void signal_herd(int signal)
{
	printf("\n");
	exit(128);	
}


int  open_heredoc(t_cmds *cmds)
{
	static int  i;
	static int	k;
	char    	*tmp1;
	char    	*filename;
	char    	*line;
	bool    	flag;
	int     	fd;
	int status;
	
	
	int fd0 = dup(0);
	flag = true;
	if (check_quot(cmds->cmd[0]) != 0)
		flag = false;
	tmp1 = ft_itoa(i);
	filename = ft_strjoin("/tmp/HereDoc", tmp1);
	free(tmp1);

		// this part is only froking for the heredoc, it doesn't handel any thing in seg, if u wanna test it
		// remove any thing about seg in this function
	int pid = fork();
	if (pid == 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		signal(SIGINT, signal_herd);
		line = readline(">");
		while (1)
		{
			k++;
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
			{
				break;
			}
			if (flag == true)
				line = expand_variable(line, cmds->data);
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
			free(line);
			line = readline(">");
		}
		close(fd);
		exit(0);
	}
	else if (pid < 0)
	    ft_putstr_fd("minishell: fork fail while creating the HereDocument\n", 2);

	
	waitpid(pid,&status,0);
	if (status != 0)
		return (1);
	return (0);
		

	dup2(fd0, 0);
	close(fd0);
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
	int		heredoc_num = 0;
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
	curr = head;
	while (curr)
	{
		if (heredoc_num > 16)
		{
			ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
			exit(2);
		}
		if (curr->token == HereDoc)
			heredoc_num++;
		curr = curr->next;
	}
	while (head)
	{
		if (head->token == HereDocDel)
		{
			if (open_heredoc(head))
				break;
		}
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
