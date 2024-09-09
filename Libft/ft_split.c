/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:39:39 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 11:57:07 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

static int	count(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s && *s)
	{
		if (*s == c || *s == '	')
			in_word = 0;
		else
		{
			if (in_word == 0 && (*s != c && *s != '	'))
			{
				count++;
				in_word = 1;
			}
		}
		s++;
	}
	return (count);
}

static void	ft_free(char **ptr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(ptr[j++]);
	free(ptr);
}

char const	*get_index(char const *s, char c)
{
	char	tmp;

	while (*s && ((*s != c && *s != '	')))
	{
		if ((*s == 39 || *s == 34) && s[1])
		{
			tmp = *s;
			while (++s && s && s[1] && *s != tmp)
			{
			}
		}
		s++;
	}
	return (s);
}

static char	**split(char const *s, char c, int i, char **ptr)
{
	const char	*start;

	while (*s)
	{
		if (*s != c && *s != '	')
		{
			start = s;
			s = get_index(s, c);
			ptr[i] = ndup(start, s - start);
			if (ptr[i] == NULL)
			{
				ft_free(ptr, i);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = count(s, c);
	ptr = malloc((word_count + 1) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (split(s, c, 0, ptr));
}
