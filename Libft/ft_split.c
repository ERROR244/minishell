/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:38:13 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 16:38:53 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	**ft_free2(char **fr)
{
	size_t	i;

	i = 0;
	while (fr[i])
	{
		free(fr[i]);
		i++;
	}
	free (fr);
	return (0);
}

static char	*small_alloc(char const *str, int *index, char separator)
{
	char	*ptr;
	int		len;
	int		pos;
	int		k;

	len = 0;
	while (str[*index] == separator && str[*index])
		(*index)++;
	pos = *index;
	while (str[*index] != separator && str[*index])
		(*index)++;
	len = *index - pos;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (*ft_free2(&ptr));
	k = 0;
	while (k < len)
	{
		ptr[k] = str[pos];
		k++;
		pos++;
	}
	ptr[k] = '\0';
	return (ptr);
}

static int	count_words(char const *str, char c)
{
	size_t	wo;
	size_t	i;

	wo = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			wo++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (wo);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		count;
	int		j;

	j = 0;
	if (s == NULL)
		return (NULL);
	count = count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	ptr[count] = NULL;
	i = 0;
	while (j < count)
	{
		ptr[j] = small_alloc(s, &i, c);
		j++;
	}
	return (ptr);
}
