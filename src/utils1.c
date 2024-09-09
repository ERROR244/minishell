/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/11 09:26:41 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	how_many_dollar_in(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str && str[i])
	{
		if (str[i] && str[i] == 39 && check_ex(str, i) == true)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
		}
		else if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] != '$')
		{
			k++;
			i++;
		}
		else if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
			i++;
		if (str[i])
			i++;
	}
	return (k + 1);
}

int	lenofmyenv(char **env)
{
	int	i;
	int	mylen;

	i = 0;
	mylen = 0;
	while (env[i])
	{
		i++;
		mylen++;
	}
	return (mylen);
}

t_env	*findmyindex(t_env *list, char *va)
{
	int	len;

	len = ft_strlen(va);
	while (list)
	{
		if (ft_strncmp(list->var_name, va, len) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

char	*ft_strjoin3(char const *s1, char c, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (s1 == NULL && s2 != NULL)
		return (ft_strdup((char *)s2));
	if (s2 == NULL && s1 != NULL)
		return (ft_strdup((char *)s1));
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (ptr == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

void	insert_var_node_in_list(t_env *index, t_env *node)
{
	if (index && node)
	{
		node->next = index->next;
		node->prev = index;
		if (index->next)
			index->next->prev = node;
		index->next = node;
	}
}
