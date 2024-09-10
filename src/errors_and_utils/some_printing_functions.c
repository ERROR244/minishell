/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:31:09 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 09:38:23 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// debug function
void	print_array(char **str)
{
	if (!str || !*str)
		return ;
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

void	ft_puterror_fd(char *str1, char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}

void	print_value(char *str)
{
	while (str && *str && *str != '=')
	{
		printf("%c", *str);
		str++;
	}
	if (str && *str)
	{
		printf("=\"");
		str++;
		while (str && *str)
		{
			printf("%c", *str);
			str++;
		}
		printf("\"");
	}
	printf("\n");
}
