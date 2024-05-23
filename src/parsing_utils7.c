/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/23 16:34:34 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../Libft/libft.h"

int cheak_num(char *s)
{
	char *start;

	start = s;
	s++;
	while (ft_isalpha(*s) == 1)
		s++;
	if (ft_isdigit(*s) == 1)
		return (s - start);
	return (0);
}

static int	count(char *s1)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s1 && *s1)
	{
		if (*s1 == '$' && cheak_num(s1) != 0)
		{
			while (ft_isdigit(*s1) == 0)
				s1++;
			s1++;
		}
		if (*s1 == '$' && ft_isalpha(s1[1]) == 1)
        {
            s1++;
			if (*s1 != '$')
            {
                while (*s1 && ft_isalpha(s1[0]) == 1)
			    {
					// printf("----->:$%c:\n", *s1);
                    s1++;
                }
			    in_word = 0;
            }
        }
		else if (in_word == 0)
		{
		    count++;
			// printf(":");
            while (*s1 && (*s1 != '$' || (ft_isalnum(s1[0]) == 1) || !s1[1]))
		    {
				// printf("%c", *s1);
				if (s1[0] == '$' && s1[1] == '$')
				{
					s1++;
					// printf("%c", *s1);
				}
                s1++;
            }
			// printf(":\n");
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
	size_t	j;

	if (!s)
		return (NULL);
	dup = (char *)malloc((n + 1) * sizeof(char));
	if (dup != NULL)
	{
		j = 0;
		i = 0;
		while (j < n)
		{
			if (s[i] == '$' && cheak_num(s) != 0)
			{
				while (ft_isdigit(s[i]) == 0)
					i++;
				i++;
			}
			dup[j] = s[i];
			i++;
			j++;
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
	int		flag;

	while (*s1)
	{
		
		if (*s1 != '$' || ft_isalnum(s1[1]) == 0)
		{
			flag = 0;
			start = s1;
            while (*s1)
            {
				if (*s1 == '$' && cheak_num(s1) != 0)
				{
					flag += cheak_num(s1) + 1;
					while (ft_isdigit(*s1) == 0)
						s1++;
					s1++;
					printf(":%c:\n", *s1);
				}
                if (*s1 == '$' && ft_isalnum(s1[1]) == 0)
                    s1++;
				else if (*s1 == '$')
					break ;
				printf("_________________________>%c \n", *s1);
				s1++;
            }
			printf("flag----->%d \n", flag);
			printf("%ld \n", s1 - start - flag);
			ptr[i] = dup_size(start, s1 - start - flag);
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
            while (*s1 && ft_isalpha(*s1) == 1)
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
    // printf("%d \n", word_count);
    // return (NULL);
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
