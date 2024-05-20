/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/20 18:52:12 by ksohail-         ###   ########.fr       */
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

const char	*inword(char const *s, char const *start)
{
	char c1;
	char c2;
	int size = s - start;
	int i;
	int one;
	int two;



	one = 0;
	two = 0;
	i = 0;
	while (i <= size)
	{
		if (start[i] == 39)
		{
			c1 = start[i];
			one++;
			while (++i <= size)
			{
				if (start[i] == c1)
				{
					one++;
					break;
				}
			}
			if (one == 2)
				one = 0;
		}
		i++;
	}

	i = 0;
	while (i <= size)
	{
		if (start[i] == 34)
		{
			c2 = start[i];
			two++;
			while (++i <= size)
			{
				if (start[i] == c2)
				{
					two++;
					break;
				}
			}
			if (two == 2)
				two = 0;
		}
		i++;
	}

	
	
	if (one != 0 && one == 2)
	{
		while (*s && (*s != c1))
			s++;
	}
	else if (two != 0 && two == 2)
	{
		while (*s && (*s != c2))
			s++;
	}
	return (s);
}

char const	*get_position(char const *s, char const	*start_tmp)
{
	while (*s && (*s != '|' && *s != '<' && *s != '>'))
		s++;
	s = inword(s, start_tmp);
	while (*s && (*s != '|' && *s != '<' && *s != '>'))
		s++;
	return (s);
}

static char	**split(char const *s, int i, char **ptr, int k)
{
	char const	*start;
	char const	*start_tmp;
	
	start_tmp = s;
	while (*s)
	{
		k = 1;
		if ((*s != '|' && *s != '<' && *s != '>'))
		{
			start = s;
			s = get_position(s, start_tmp);
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
	word_count = count_words(s);// - inside(s);
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
