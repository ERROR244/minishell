/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:31:09 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 16:33:07 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_array(char **str)
{
	printf(":");
	while (str && *str)
	{
		printf("%s-", *str);
		str++;
	}
	printf(":");
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