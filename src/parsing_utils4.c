/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/27 09:41:46 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void get_list(char **cmd, int size, t_cmds **lst, t_data *data)
{
	t_cmds *node;
	t_cmds *curr;
	int i;
	
	i = 0;
	if (cmd[0] == NULL)
	{
		*lst = lstnew("\n", *lst);
		return ;
	}
	*lst = lstnew(cmd[i++], *lst);
	(*lst)->data = data;
	while (i < size)
	{
		node = lstnew(cmd[i], *lst);
		node->data = data;
		curr = lstlast(*lst);
		curr->next = node;
		i++;
	}
}

char *rm_spaces(char *str)
{
	int i;
	int k;
	int l;
	char *ptr;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	l = i;
    k = i;
	while (str[i++])
        l++;
    i--;
    while (--i != 0 && (str[i] == ' ' || str[i] == '	'))
	{
        l--;
	}
	ptr = malloc(sizeof(char) * (l - k + 1));
    i = 0;
	while (k < l)
		ptr[i++] = str[k++];
	ptr[i] = '\0';
	free(str);
	return (ptr);
}

int	count_words(char const *s)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	if (s[0] == '\0')
		return (1);
	while (s && *s)
	{
		if (*s == '|' || *s == '<' || *s == '>')
		{
			if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
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
