/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/21 12:55:19 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t get_size(char *str)
{
	size_t	k;
	size_t	i;
	char	tmp;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i];
			while (str[++i] != tmp)
			{
				
			}
			k += 2;
		}
		i++;
	}
	return (i - k);
}

static char	*get_string(char *str, size_t i, size_t k)
{
	char	*ptr;
	char	tmp;
	size_t	size;

	if (!str)
		return NULL;
	size = get_size(str);
	if (size == ft_strlen(str))
		return (str);
	ptr = malloc(sizeof(char) * (size + 1));
	while (k < size)
	{
		if (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i++];
			while (str[i] != tmp)
				ptr[k++] = str[i++];
			i++;
		}
		ptr[k++] = str[i++];
	}
	ptr[k] = '\0';
	free(str);
	return (ptr);
}

void	remove_quotes(t_cmds *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		while (lst->cmd[i])
		{
			lst->cmd[i] = get_string(lst->cmd[i], 0, 0);
			i++;
		}
		lst = lst->next;
	}
}