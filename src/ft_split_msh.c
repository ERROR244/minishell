/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/20 16:55:12 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_words(char const *s)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s && *s)
	{
		if (*s == '|' || *s == '<' || *s == '>')
		{
			if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>'))
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

static void	ft_free(char **ptr, int i)
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

static char	**split(char const *s, int i, char **ptr, int k)
{
	const char	*start;
	char flag;

	while (*s)
	{
		k = 1;
		if (*s != '|' && *s != '<' && *s != '>')
		{
			start = s;
			while (*s && (*s != '|' && *s != '<' && *s != '>'))
				s++;
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
	word_count = count_words(s);
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
