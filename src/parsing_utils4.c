/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/07 11:57:34 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_file_name(char *str)
{
	char	**ptr;
	int		size;
	int		i;

	size = 0;
	i = 0;
	ptr = malloc(sizeof(char *) * (3));
	while (str[size] && str[size] != 32 && str[size] != 9)
		size++;
	ptr[0] = malloc(sizeof(char) * (size + 1));
	ft_strlcpy(ptr[0], str, size + 1);
	if (!str[size])
	{
		ptr[1] = NULL;
		return (ptr);
	}
	i = 0; 
	while (str[i])
		i++;
	ptr[1] = malloc(sizeof(char) * (i - size + 1));
	ft_strlcpy(ptr[1], str + size, ft_strlen(str + size) + 1);
	ptr[2] = NULL;
	return (ptr);
}

int	is_space_in(char *str)
{
	int i;
	int j;

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

void get_list(char **cmd, int size, t_cmds **lst, t_data *data)
{
	t_cmds *node;
	t_cmds *curr;
	char **ptr;
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
		if (cmd[i - 1][0] == '<' && is_space_in(cmd[i]) == 0)
		{
			ptr = get_file_name(cmd[i]);
			node = lstnew(ptr[0], *lst);
			node->data = data;
			curr = lstlast(*lst);
			curr->next = node;
			if (ptr[1])
			{
				node->data = data;
				node = lstnew(ptr[1], *lst);
				curr = lstlast(*lst);
				curr->next = node;
			}
			free_array(ptr);
			if (++i == size)
				return ;
		}
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
