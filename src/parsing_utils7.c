/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/22 18:26:48 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlen_to_split(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp_to_split(char *s1, char *s2, int n)
{
	while (n > 0)
	{
        if (*s1 == '\0')
			return (1);
		if (*s2 == '\0')
			return (0);
		if (*s1 != *s2)
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}

static int	count(char *s1, char *s2)
{
	int	count;
	int	in_word;
    int same;
    int tmp;

	count = 0;
	in_word = 0;
    int size = ft_strlen_to_split(s2);
	while (s1 && *s1)
	{
        same = ft_strcmp_to_split(s1, s2, size);
		if (same == 0)
			in_word = 0;
		else
		{
			if (in_word == 0)
			{
				count++;
                tmp = 0;
                while (++tmp < size && s1)
			        s1++;
                printf("%d<->%d \n", size - 1, tmp);
			    in_word = 1;
			}
		}
		s1++;
	}
	return (count);
}

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

static char	**split(char *s1, char *s2, int i, char **ptr)
{
	char	*start;
    int         size;
    int tmp = 0;

    size = ft_strlen_to_split(s2);
	while (*s1)
	{
		if (ft_strcmp_to_split(s1, s2, size) != 0)
		{
			start = s1;
			while (*s1 && ft_strcmp_to_split(s1, s2, size) != 0)
            {
                tmp = 0;
                while (++s1)
                {
                    if (ft_strcmp_to_split(s1, s2, size) == 0)
                        break ;
                }
            }
			ptr[i] = dup_size(start, s1 - start);
			if (ptr[i] == NULL)
			{
				ft_free(ptr, i);
				return (NULL);
			}
			i++;
		}
		else
        {
            tmp = 0;
            while (++s1 && ++tmp < size)
            {
            }
        }
	}
    printf("\n");
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split_str(char *s1, char *s2)
{
	char	**ptr;
	int		word_count;

	if (s1 == NULL)
		return (NULL);
	word_count = count(s1, s2);
    printf("%d \n", word_count);
    if (word_count == 0)
        return (NULL);
	ptr = malloc((word_count + 1) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (split(s1, s2, 0, ptr));
}


void free_split_array(char **split_array)
{
    char **ptr = split_array;
    while (*ptr) {
        free(*ptr);
        ptr++;
    }
    free(split_array);
}

int main(int ac, char **av)
{
    char **result = ft_split_str(av[1], av[2]);

    if (result)
	{
        for (int i = 0; result[i]; i++)
		{
            printf(":%s:\n", result[i]);
        }

        free_split_array(result);
    }
	else
	{
        printf("Error: ft_split returned NULL\n");
    }

    return 0;
}
