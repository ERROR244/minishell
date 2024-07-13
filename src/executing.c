/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 11:50:43 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	change_underscore(t_data *data, t_command *command, char *str, int i)
{
	t_env	*index;

	if (!command->cmd || !command->cmd[0])
		return (false);
	while (command->cmd[i])
		i++;
	str = command->cmd[--i];
	if (!str || *str == '\n')
		return (false);
	index = findmyindex(data->list_env, "_");
	if (index)
	{
		free(index->var_name);
		index->var_name = ft_strjoin("_=", str);
	}
	else
	{
		index = env_new(data->list_env, ft_strjoin("_=", str));
		data->list_env = env_last(data->list_env);
		if (data->list_env)
			data->list_env->next = index;
		else
			data->list_env = index;
	}
	return (true);
}

int	run_builtins(int c, t_command *command, t_data *data, int flag)
{
	t_env	*list;

	list = data->list_env;
	if (c == 1)
		my_cd(list, command->cmd);
	else if (c == 2)
		mypwd(list);
	else if (c == 3)
		printmyenv(list);
	else if (c == 4)
		export(list, command->cmd, '-', 1);
	else if (c == 5)
		data->list_env = unset_env(list, command->cmd, data);
	else if (c == 6)
		exit_myminishell(command->cmd, flag);
	else if (c == 7)
		ft_echo(command->cmd + 1, true, 0);
	return (0);
}

void	only_builtins(t_data *data, t_command *list, int builtins)
{
	int			in;
	int			out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (list->infile || list->outfile)
		g_signal.ret = hand_the_redirectionin(list);
	if (g_signal.ret != 1)
		run_builtins(builtins, list, data, 0);
	if ((g_signal.ret != 1) && list->infile)
		dup2(in, STDIN_FILENO);
	else
		ft_close(in, "in");
	if ((g_signal.ret != 1) && list->outfile)
		dup2(out, STDOUT_FILENO);
	else
		ft_close(out, "out");
}

void	with_pipe(t_data *data, t_command *list)
{
	data->k = 0;
	data->pid = malloc(sizeof(int) * (get_command_size(list)));
	data->fd_in = STDIN_FILENO;
	while (list)
	{
		if (list->next)
		{
			if (pipe(data->fd) == -1)
				break ;
		}
		g_signal.ret = execute_command(data->list_env, list, data,
				data->k++);
		if (list->next)
			ft_close(data->fd[1], "data->fd[0]");
		if (list->prev)
			ft_close(data->fd_in, "data->fd[1]");
		if (list->next)
			data->fd_in = data->fd[0];
		list = list->next;
	}
	if (g_signal.ret == 0 && data->k != 0)
		g_signal.ret = wait_pid(data->pid, data->k);
	free(data->pid);
	data->pid = NULL;
}

int	executing(t_data *data)
{
	t_command	*list;
	int			builtins;
	bool		flag;

	list = data->list;
	flag = false;
	builtins = get_command_in_one_char(list->cmd);
	if (!list || (list->cmd && list->cmd[0][0] == '\n'))
		return (2);
	if (!list->next)
		flag = change_underscore(data, list, NULL, 0);
	if (builtins != 0 && !list->next)
		only_builtins(data, list, builtins);
	else
		with_pipe(data, list);
	if (flag == true)
		change_underscore(data, list, NULL, 0);
	g_signal.ret_exit = g_signal.ret;
	return (g_signal.ret);
}
