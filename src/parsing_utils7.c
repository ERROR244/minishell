/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/22 19:52:15 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count(char *s1)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s1 && *s1)
	{
		if (*s1 == '$')
        {
            s1++;
            if (*s1 == ' ' || *s1 == '\n' || *s1 == ':' || *s1 == '$')
            {
                count++;
            }
            else if (*s1 != '$')
            {
                while (*s1 && (*s1 != ' ' && *s1 != '\n' && *s1 != ':' && *s1 != '$'))
			    {
                    s1++;
                }
			    in_word = 0;
            }
        }
		else if (in_word == 0)
		{
		    count++;
            while (*s1 && *s1 != '$')
		    {
                s1++;
            }
		    in_word = 1;
		}
        else
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

static char	**split(char *s1, int i, char **ptr)
{
	char	*start;
    int         size;

	while (*s1)
	{
		if (*s1 != '$')
		{
			start = s1++;
            while (*s1)
            {
                s1++;
                if (*s1 == '$')
                    break ;
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
            s1++;
            while (*s1 && (*s1 != ' ' && *s1 != '\n' && *s1 != ':' && *s1 != '$'))
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
	word_count = count(s1);
    printf("%d \n", word_count);
    return (NULL);
	ptr = malloc((word_count + 1) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (split(s1, 0, ptr));
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
    char **result = ft_split_str(av[1]);

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
