/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 09:07:47 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_in(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '	')
			i++;
		if (*str == ' ' || *str == '	')
			j++;
		str++;
	}
	if (i == 0 || j == 0)
		return (1);
	return (0);
}

void	get_list(char **cmd, int size, t_cmds **lst, t_data *data)
{
	t_cmds	*node;
	t_cmds	*curr;
	int		i;

	i = 0;
	if (cmd[0] == NULL)
	{
		*lst = lstnew("\n", *lst, NULL);
		return ;
	}
	*lst = lstnew(cmd[i++], *lst, NULL);
	(*lst)->data = data;
	while (i < size)
	{
		node = lstnew(cmd[i], *lst, NULL);
		node->data = data;
		curr = lstlast(*lst);
		curr->next = node;
		i++;
	}
}
