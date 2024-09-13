/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 09:12:05 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_herd(int pid)
{
	(void)pid;
	printf("\n");
	ft_exit(130);
}

int	print_error(int k, char *str)
{
	char	*num;

	num = ft_itoa(k);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(num, 2);
	free(num);
	ft_putstr_fd("  delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
	return (0);
}

void	check_quot_and_filename(bool *flag, char **filename, char *str)
{
	static int	i;
	char		*tmp1;

	if (check_quot(str) != 0)
		*flag = false;
	tmp1 = ft_itoa(i);
	*filename = ft_strjoin("/tmp/HereDoc", tmp1);
	free(tmp1);
}

void	child(char *line, t_cmds *cmds, bool flag)
{
	int			k;
	int			fd;

	fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	free(line);
	signal(SIGINT, signal_herd);
	line = readline(">");
	k = 1;
	while (1)
	{
		if (!line && print_error(k, cmds->cmd[0]) == 0)
			break ;
		else if (ft_strcmp_for_heredoc(line, cmds->cmd[0]) == 0)
			break ;
		k++;
		if (flag == true)
			line = expand_variable(line, cmds->data);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline(">");
	}
	close(fd);
	ft_exit(0);
}

int	open_heredoc(t_cmds *cmds, int pid, int status, bool flag)
{
	char		*line;
	int			fd0;

	fd0 = dup(0);
	check_quot_and_filename(&flag, &line, cmds->cmd[0]);
	g_signal.ff = 1;
	pid = ft_fork();
	if (pid == 0)
		child(line, cmds, flag);
	else if (pid < 0)
		ft_putstr_fd("minishell: fork fail while creating the HereDoc\n", 2);
	waitpid(pid, &status, 0);
	g_signal.ff = 0;
	dup2(fd0, 0);
	close(fd0);
	free(cmds->cmd[0]);
	cmds->cmd[0] = line;
	cmds->prev->token = Input;
	cmds->token = Infile;
	if (status != 0)
		return (130);
	return (0);
}
