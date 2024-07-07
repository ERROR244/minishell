/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 10:09:31 by ksohail-         ###   ########.fr       */
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

int	errormsg(char *str)
{
	ft_put2str_fd("minishel: syntax error near unexpected token", str, 2);
	return (2);
}

int	check_quot(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
			i++;
		str++;
	}
	return (i);
}

int	get_command_size(t_command *command)
{
	int	size;

	size = 0;
	while (command)
	{
		command = command->next;
		size++;
	}
	return (size);
}

int	wait_pid(int *pid, int cmd_num)
{
	int	i;
	int	status;

	if (cmd_num == 0)
		return (0);
	i = cmd_num;
	status = 0;
	waitpid(pid[--i], &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (i >= 0)
		waitpid(pid[i--], 0, 0);
	if (g_signal.ret == 130)
		return (130);
	return (status);
}
