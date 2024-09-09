/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:39:39 by ksohail-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/04 17:45:49 by ksohail-         ###   ########.fr       */
=======
/*   Updated: 2024/07/13 11:57:07 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
<<<<<<< HEAD

static int	count_words(char const *s, char c)
=======
#include "../include/minishell.h"

static int	count(char const *s, char c)
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s && *s)
	{
<<<<<<< HEAD
		if (*s == c)
			in_word = 0;
		else
		{
			if (in_word == 0 && *s != c)
=======
		if (*s == c || *s == '	')
			in_word = 0;
		else
		{
			if (in_word == 0 && (*s != c && *s != '	'))
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
			{
				count++;
				in_word = 1;
			}
		}
		s++;
	}
	return (count);
}

<<<<<<< HEAD
static char	*ndup(const char *s, size_t n)
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

=======
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
static void	ft_free(char **ptr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(ptr[j++]);
	free(ptr);
}

<<<<<<< HEAD
=======
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

>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
static char	**split(char const *s, char c, int i, char **ptr)
{
	const char	*start;

	while (*s)
	{
<<<<<<< HEAD
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
=======
		if (*s != c && *s != '	')
		{
			start = s;
			s = get_index(s, c);
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
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
<<<<<<< HEAD
	word_count = count_words(s, c);
=======
	word_count = count(s, c);
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
	ptr = malloc((word_count + 1) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (split(s, c, 0, ptr));
}
