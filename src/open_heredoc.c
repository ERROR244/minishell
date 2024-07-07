/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 10:09:31 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_herd(int pid)
{
	(void)pid;
	printf("\n");
	exit(128);
}

int	open_heredoc(t_cmds *cmds)
{
	static int	i;
	static int	k;
	char		*tmp1;
	char		*filename;
	char		*line;
	bool		flag;
	int			fd;
	int			status;
	int			fd0;
	int			pid;
	char		*num;

	fd0 = dup(0);
	flag = true;
	if (check_quot(cmds->cmd[0]) != 0)
		flag = false;
	tmp1 = ft_itoa(i);
	filename = ft_strjoin("/tmp/HereDoc", tmp1);
	free(tmp1);
	g_signal.ff = 1;
	pid = fork();
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
				num = ft_itoa(k);
				ft_putstr_fd("minishell: warning: here-document at line ", 2);
				ft_putstr_fd(num, 2);
				free(num);
				ft_putstr_fd("  delimited by end-of-file (wanted `", 2);
				ft_putstr_fd(cmds->cmd[0], 2);
				ft_putstr_fd("')\n", 2);
				break ;
			}
			else if (ft_strcmp_for_heredoc(line, cmds->cmd[0]) == 0)
			{
				break ;
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
		ft_putstr_fd("minishell: fork fail while creating the HereDocument\n",
			2);
	waitpid(pid, &status, 0);
	g_signal.ff = 0;
	dup2(fd0, 0);
	close(fd0);
	free_array(cmds->cmd);
	cmds->cmd = malloc(sizeof(char *) * 2);
	cmds->cmd[0] = filename;
	cmds->cmd[1] = NULL;
	cmds->prev->token = Input;
	cmds->token = Infile;
	i++;
	if (status != 0)
		return (130);
	return (0);
}
