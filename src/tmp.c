/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:31:09 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/08 16:05:38 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_array(char **str)
{
	printf(":");
	printf("%s", *str);
	str++;
	while (str && *str)
	{
		printf(" <-> %s", *str);
		str++;
	}
	printf(":\n");
}

void	printlist(void *tmp)
{
	t_slist *list;

	list = tmp;
	while (list)
	{
		print_array(list->cmd);
		list = list->next;
	}
}

void	ft_close(int fd, char *str)
{
	int	n;

	n = close(fd);
	if (n == -1)
	{
		printf("Right Fucking here %s\n", str);
		exit(1);
	}
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
