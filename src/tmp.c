/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:31:09 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 14:33:34 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	print_array(char **str)
// {
// 	if (!str || !*str)
// 		return ;
// 	printf(":");
// 	printf("%s", *str);
// 	str++;
// 	while (str && *str)
// 	{
// 		printf(" <-> %s", *str);
// 		str++;
// 	}
// 	printf(":\n");
// }

// void	printlist(void *tmp)
// {
// 	t_slist	*list;

// 	list = tmp;
// 	while (list)
// 	{
// 		list = list->next;
// 	}
// }

void	ft_puterror_fd(char *str1, char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}
