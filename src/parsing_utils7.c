/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/28 13:06:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
bool	check_ex(char *str, int size);

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

bool	check_next(char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == 34)
			flag++;
		i++;
	}
	// printf("%d", flag);
	if (flag % 2 == 0)
		return (true);
	return (false);
}

static char	**split(char *s1, int i, char **ptr)
{
	char	*start;
	// char	*tmp = s1;
	bool	flag;

	while (s1 && *s1)
	{
		if (*s1 != '$' || ft_isalnum(s1[1]) == 0)
		{

			start = s1;
            while (*s1)
            {
				flag = check_next(s1);
				// printf("<>%c<>%d<>\n", *s1, flag);
				if (*s1 == 39 && flag == true)
				{
					s1++;
					while (*s1 != 39)
					{
						// printf("------>%c \n", *s1);
						s1++;
					}
				}
				else if (flag == false && s1[1] == '$')
				{
					// printf("------>%c \n", *s1);
					s1++;
				}
				// printf("------>%c \n", *s1);
				if ((*s1 == '$' && ft_isalnum(s1[1]) == 0) || *s1 == 39)
                    s1++;
				else if (*s1 == '$')
					break ;
				if (!*s1)
					break;
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

// #include "../include/minishell.h"

// int main(int ac, char **av)
// {
//     char **result = ft_split_str("echo '$PWD'   The current user is $USER. to your home directory: \" '$HOME'\".");
//     // char **result = ft_split_str(av[1]);

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


// bool	check_ex(char *str, int size)
// {
// 	int i;
// 	int flag;

// 	i = 0;
// 	if (size == 0)
// 		return (true);
// 	flag = 0;
// 	while (str[i] && i <= size)
// 	{
// 		if (str[i] == 34)
// 			flag++;
// 		i++;
// 	}
// 	if (flag % 2 == 0)
// 		return (true);
// 	return (false);
// }