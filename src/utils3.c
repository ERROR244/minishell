/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 19:59:31 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_command_in_one_char(char **str)
{
	int	c;

	c = 0;
	if (ft_strcmp(str[0], "cd") == 0)
		c = 1;
	else if (ft_strcmp(str[0], "pwd") == 0)
		c = 2;
	else if (ft_strcmp(str[0], "env") == 0 && str[1] == NULL)
		c = 3;
	else if (ft_strcmp(str[0], "export") == 0)
		c = 4;
	else if (ft_strcmp(str[0], "unset") == 0)
		c = 5;
	else if (ft_strcmp(str[0], "exit") == 0)
		c = 6;
	else if (ft_strcmp(str[0], "echo") == 0)
		c = 7;
	return (c);
}

int	execute_command(t_env *list, t_command *command, t_data *data, int index)
{
	char	*path;
	int		cmd;
	int		red;
	char	**com;

	red = 0;
	if (!command->cmd)
		return (-1);
	com = command->cmd;
	if (com[0][0] == '\0')
	{
		if (data->flag != true)
			return (0);
		ft_putstr_fd("minishell: command '' not found\n", 2);
		return (127);
	}
	cmd = get_command_in_one_char(com);
	path = get_my_path(list, com, data->path_flag, 0);
	signal(SIGINT, SIG_IGN);
	data->pid[index] = fork();
	if (data->pid[index] == 0)
	{
		signal(SIGINT, SIG_DFL);
		free(data->line);
		if (command->infile || command->outfile)
			red = hand_the_redirectionin(command);
		if (red == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(com[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			senv_clear(&data->list_env);
			free_array(data->env);
			exit(-1);
		}
		if (path == NULL && cmd == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(com[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			senv_clear(&data->list_env);
			free_array(data->env);
			exit(127);
		}
		if (command->prev && !command->infile)
		{
			dup2(data->fd_in, STDIN_FILENO);
			ft_close(data->fd_in, "fd_in\n");
		}
		if (command->next && !command->outfile)
			dup2(data->fd[1], STDOUT_FILENO);
		if (command->next)
		{
			ft_close(data->fd[1], "fd[0]/n");
			ft_close(data->fd[0], "fd[1]/n");
		}
		if (cmd == 0)
		{
			if (signal(SIGQUIT, printsignalsc) != SIG_ERR)
				g_signal.ret = 131;
			execve(path, com, data->env);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(com[0], 2);
			ft_putstr_fd(": ", 2);
			struct stat stats;
			if (stat(path, &stats) == 0)
				ft_putstr_fd("Is a directory", 2);
			else
				ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			senv_clear(&data->list_env);
			free_array(data->env);
			exit(-1);
		}
		else
			run_builtins(cmd, command, data, 1);
		senv_clear(&data->list_env);
		free_array(data->env);
		exit(0);
	}
	free(path);
	if (data->pid[index] < 0)
		return (-1);
	return (0);
}
