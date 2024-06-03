/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:31:09 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/03 18:14:57 by ksohail-         ###   ########.fr       */
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

void	printlistenv(void *tmp)
{
	t_env *list;

	list = tmp;
	while (list)
	{
		printf("%s\n", list->var_name);
		list = list->next;
	}
}
