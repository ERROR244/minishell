/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/25 16:30:09 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	char c;
	int i;

	i = 0;
	while (*s)
	{
		if (*s == 39 || *s == 34)
		{
			c = *s;
			while (++s && *s)
			{
				if (*s == '|' || *s == '<' || *s == '>')
				{
					if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
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
	char c;

	while (*s && (*s != '|' && *s != '<' && *s != '>'))
	{
		if (*s == 39 || *s == 34)
		{
			c = *s;
			while (++s && *s != c) {}
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
			if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
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

char	**ft_split_msh(char const *s)
{
	char	**ptr;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s) - inside(s);
	ptr = malloc((word_count + 1) * sizeof(char *));
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr = split(s, 0, ptr, 1);
	return (ptr);
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
//     const char *test_string = av[1];

//     char **result = ft_split_msh(test_string);

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
