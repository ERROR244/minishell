/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/11 12:12:40 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_command_in_one_char(char **str)
{
	int	c;

	c = 0;
	if (!str || !*str)
		return (c);
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

void	execute_command_part_one(char **com, t_command *command, t_data *data,
		char *path)
{
	int	red;

	red = 0;
	signal(SIGINT, SIG_DFL);
	free(data->line);
	if (command->infile || command->outfile)
		red = hand_the_redirectionin(command);
	if (red == 1)
	{
		senv_clear(&data->list_env);
		free_array(data->env);
		exit(1);
	}
	else if (path == NULL && get_command_in_one_char(com) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(com[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		senv_clear(&data->list_env);
		free_array(data->env);
		exit(127);
	}
}

void	execute_command_part_two(t_command *command, t_data *data)
{
	if (command->prev && !command->infile)
	{
		dup2(data->fd_in, STDIN_FILENO);
		ft_close(data->fd_in, "fd_in\n");
	}
	if (command->next && !command->outfile)
		dup2(data->fd[1], STDOUT_FILENO);
	if (command->next)
	{
		ft_close(data->fd[1], "fd[0]\n");
		ft_close(data->fd[0], "fd[1]\n");
	}
}

void	execute_command_part_three(char **com, t_command *command, t_data *data,
		char *path)
{
	struct stat	stats;
	int			cmd;

	cmd = get_command_in_one_char(com);
	if (cmd == 0)
	{
		if (signal(SIGQUIT, printsignalsc) != SIG_ERR)
			g_signal.ret = 131;
		execve(path, com, data->env);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(com[0], 2);
		ft_putstr_fd(": ", 2);
		stat(path, &stats);
		if (S_ISDIR(stats.st_mode))
			ft_putendle("Is a directory", 2);
		else
			ft_putendle(strerror(errno), 2);
		senv_clear(&data->list_env);
		free_array(data->env);
		exit(-1);
	}
	else
		run_builtins(cmd, command, data, 1);
	senv_clear(&data->list_env);
	free_array(data->env);
}

int	execute_command(t_env *list, t_command *command, t_data *data, int index)
{
	char	*path;

	if (!command->cmd)
		return (-1);
	if (command->cmd[0][0] == '\0' && !command->infile && !command->outfile)
	{
		ft_putstr_fd("minishell: command '' not found\n", 2);
		return (127);
	}
	path = get_my_path(list, command->cmd, data->path_flag, 0);
	signal(SIGINT, SIG_IGN);
	data->pid[index] = ft_fork();
	if (data->pid[index] == 0)
	{
		execute_command_part_one(command->cmd, command, data, path);
		execute_command_part_two(command, data);
		if (command->cmd[0][0] != '\0')
			execute_command_part_three(command->cmd, command, data, path);
		exit(0);
	}
	free(path);
	if (data->pid[index] < 0)
		return (-1);
	return (0);
}
