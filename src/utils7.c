/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 09:24:07 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void ft_clear(t_data *data)
{
    t_cmds *cur;

	cur = data->lst;
	while (cur)
	{
		free_array(cur->cmd);
		cur = cur->next;
	}
	lstclear(&data->lst);
	free_array(data->cmds);
}
