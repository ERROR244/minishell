/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 11:56:33 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **ptr, int i)
{
	int	j;

	j = 0;
	if (ptr[i] != NULL)
		return ;
	while (j < i)
		free(ptr[j++]);
	free(ptr);
}

int	inside(char const *s)
{
	char	c;
	int		i;

	i = 0;
	while (*s)
	{
		if ((*s == 39 || *s == 34) && s[1])
		{
			c = *s;
			while (++s && s && s[1] && *s)
			{
				if (*s == '|' || *s == '<' || *s == '>')
				{
					if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s
								+ 1) == '>'))
						s++;
					i++;
				}
				if (*s == c)
					break ;
			}
		}
		s++;
	}
	return (i);
}

char const	*get_position(char const *s)
{
	char	c;

	while (*s && (*s != '|' && *s != '<' && *s != '>'))
	{
		if ((*s == 39 || *s == 34) && s[1])
		{
			c = *s;
			while (++s && s && s[1] && *s != c)
			{
			}
		}
		s++;
	}
	return (s);
}

static char	**split(char const *s, int i, char **ptr, int k)
{
	char const	*start;

	while (*s)
	{
		k = 1;
		if ((*s != '|' && *s != '<' && *s != '>'))
		{
			start = s;
			s = get_position(s);
			ptr[i] = ndup(start, s - start);
			ft_free(ptr, i);
		}
		else
		{
			if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s
						+ 1) == '>'))
				k++;
			ptr[i] = ndup(s, k);
			ft_free(ptr, i);
			s += k;
		}
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
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

char	**ft_split_msh(char const *s)
{
	char	**ptr;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, 0, 0) - inside(s);
	ptr = malloc((word_count + 1) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr = split(s, 0, ptr, 1);
	return (ptr);
}
