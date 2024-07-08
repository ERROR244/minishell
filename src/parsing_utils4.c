/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/08 15:38:35 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_space_in(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str != 32 && *str != 9)
			i++;
		if (*str == 32 || *str == 9)
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

int	count_words(char const *s, int count, int in_word)
{
	if (s[0] == '\0')
		return (1);
	while (s && *s)
	{
		if (*s == '|' || *s == '<' || *s == '>')
		{
			if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s
						+ 1) == '>'))
				s++;
			in_word = 0;
			count++;
		}
		else
		{
			if (in_word == 0 && (*s != '|' && *s != '<' && *s != '>'))
			{
				count++;
				in_word = 1;
			}
		}
		s++;
	}
	return (count);
}

char	*ndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)malloc((n + 1) * sizeof(char));
	if (dup != NULL)
	{
		i = 0;
		while (i < n)
		{
			dup[i] = s[i];
			i++;
		}
		dup[n] = '\0';
	}
	return (dup);
}
