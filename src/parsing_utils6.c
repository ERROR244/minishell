/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:47:27 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/25 16:25:44 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*grep_variable_name(char *line)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	if (!line)
		return (NULL);
	j = ++i;
	while (line[i] && ft_isalnum(line[i]) == 1)
		i++;
	k = i - j;
	str = malloc(sizeof(char) * (k + 1));
	if (!str)
		return (NULL);
	while (l < k)
		str[l++] = line[j++];
	str[l] = '\0';
	return (str);
}

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
			i++;
			while (str[i] != tmp)
				i++;
			k += 2;
		}
		i++;
	}
	return (i - k);
}

static char	*get_string(char *str, size_t i, size_t k, size_t size)
{
	char	*ptr;
	char	tmp;

	if (size == ft_strlen(str))
		return (str);
	ptr = malloc(sizeof(char) * (size + 1));
	while (k < size)
	{
		while (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i++];
			while (str[i] != tmp)
			{
				ptr[k++] = str[i++];
			}
			i++;
		}
		if (k == size)
			break ;
		ptr[k++] = str[i++];
	}
	ptr[k] = '\0';
	free(str);
	return (ptr);
}

void	remove_quotes(t_cmds *lst)
{
	int i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			if (lst->cmd[i] != NULL)
				lst->cmd[i] = get_string(lst->cmd[i], 0, 0, get_size(lst->cmd[i]));
			i++;
		}
		if (ft_strcmp("echo", lst->cmd[0]) == 0)
			expand_variable(lst);
		lst = lst->next;
	}
}

char	*is_the_variable_in(char **env, char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (str == NULL)
		return (NULL);
	while (env[i])
	{
		ptr = ft_strnstr(env[i], str, ft_strlen(str));
		if (ptr != NULL)
			return (ptr);
		i++;
	}
	return (NULL);
}
