/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/11 19:11:04 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_double(char *cmd, int i)
{
	while (++i && cmd[i])
	{
		if (cmd[i] == 34)
		{
			i++;
			break ;
		}
	}
	return (i);
}

void	ft_close(int fd, char *str)
{
	int	n;

	n = close(fd);
	if (n == -1)
		printf("Right here %s\n", str);
}

int	ft_fork(void)
{
	int	n;

	n = fork();
	if (n == -1)
		exit(1);
	return (n);
}

void	ft_dup2(int fd, int std)
{
	int	n;

	n = dup2(fd, std);
	if (n == -1)
		exit(1);
}

void	ft_clear(t_data *data)
{
	lstclear(&data->lst);
	free_array(data->cmds);
}
