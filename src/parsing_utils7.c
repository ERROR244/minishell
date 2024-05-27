/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/27 11:04:33 by ksohail-         ###   ########.fr       */
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

static char	**split(char *s1, int i, char **ptr)
{
	char	*start;

	while (*s1)
	{
		if (*s1 != '$' || ft_isalnum(s1[1]) == 0)
		{

			start = s1;
            while (*s1)
            {
				if (*s1 == '$' && ft_isalnum(s1[1]) == 0)
                    s1++;
				else if (*s1 == '$')
					break ;
				s1++;
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
            while (*s1 && ft_isalnum(*s1) == 1)
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
	ptr = malloc((word_count + 1) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (split(s1, 0, ptr));
}

// void free_split_array(char **split_array)
// {
//     char **ptr = split_array;
//     while (*ptr) {
//         free(*ptr);
//         ptr++;
//     }
//     free(split_array);
// }

// int main(int ac, char **av)
// {
//     char **result = ft_split_str(av[1]);

//     if (result)
// 	{
//         for (int i = 0; result[i]; i++)
// 		{
//             printf(":%s:\n", result[i]);
//         }

//         free_split_array(result);
//     }
// 	else
// 	{
//         printf("Error: ft_split returned NULL\n");
//     }

//     return 0;
// }