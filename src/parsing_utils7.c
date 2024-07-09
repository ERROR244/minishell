/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/09 09:19:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*dup_size(char *s, size_t n)
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

static void	ft_free(char **ptr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(ptr[j++]);
	free(ptr);
}

char	*get_word(char *s1)
{
	bool	flag;

	while (*s1)
	{
		flag = check_next(s1);
		if (*s1 == 39 && flag == true)
		{
			s1++;
			while (*s1 != 39)
				s1++;
		}
		else if (flag == false && s1[1] == '$')
			s1++;
		if ((*s1 == '$' && ft_isalnum(s1[1]) == 0) || *s1 == 39)
			s1++;
		else if (*s1 == '$')
			break ;
		if (!*s1)
			break ;
		s1++;
	}
	return (s1);
}

static char	**split(char *s1, int i, char **ptr, char *start)
{
	while (s1 && *s1)
	{
		if (*s1 != '$' || ft_isalnum(s1[1]) == 0)
		{
			start = s1;
			s1 = get_word(s1);
			ptr[i++] = dup_size(start, s1 - start);
			if (ptr[i - 1] == NULL)
			{
				ft_free(ptr, i - 1);
				return (NULL);
			}
		}
		else
		{
			s1++;
			while (*s1 && ft_isalpha(*s1) == 1)
				s1++;
			if ((*s1 >= '0' && *s1 <= '9') || (s1[-1] == '$' && *s1 == '?')
				|| *s1 == '_')
				s1++;
		}
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split_str(char *s1)
{
	char	**ptr;
	int		word_count;

	if (s1 == NULL)
		return (NULL);
	word_count = count_vars(s1);
	if (word_count == 0)
		return (NULL);
	ptr = malloc((word_count + 2) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (split(s1, 0, ptr, NULL));
}
