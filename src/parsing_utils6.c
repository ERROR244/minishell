/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:47:27 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/11 09:14:31 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*grep_variable_name(char *line, int i, int j, int k)
{
	int		l;
	char	*str;

	l = 0;
	if (!line)
		return (NULL);
	j = ++i;
	if (line[i] && line[i] == '?')
		return (ft_strdup("?"));
	while (line[i] && ft_isalnum(line[i]) == 1)
		i++;
	k = i - j;
	str = malloc(sizeof(char) * (k + 1));
	if (!str)
		return (NULL);
	while (l < k)
		str[l++] = line[j++];
	str[l] = '\0';
	return (str);
}

char	*in_var(char *s1, int *in_word)
{
	s1++;
	if (*s1 == '?')
	{
		s1++;
		*in_word = 0;
	}
	else if (*s1 != '$')
	{
		while (*s1 && ft_isalpha(*s1) != 0 && *s1 != '?')
			s1++;
		*in_word = 0;
	}
	return (s1);
}

int	count_vars(char *s1)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s1 && *s1)
	{
		if (*s1 == '$' && ft_isalpha(s1[1]) != 0)
			s1 = in_var(s1, &in_word);
		else if (in_word == 0)
		{
			count++;
			while (*s1 && (*s1 != '$' || ft_isalnum(s1[0]) == 1
					|| *s1 == '?' || !s1[1]))
			{
				if (s1[0] == '$' && s1[1] == '$')
					s1++;
				s1++;
			}
			in_word = 1;
		}
		else
			s1++;
	}
	return (count);
}

int	dollar_is_in(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				i += 2;
				while (str[i] == ' ')
					i++;
				while (str[i] && ft_isalpha(str[i]) == 0)
					i++;
			}
		}
		if (!str[i])
			break ;
		if (str[i] == '$')
			k++;
		i++;
	}
	return (k);
}

bool	check_next(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == 34)
			flag++;
		i++;
	}
	if (flag % 2 == 0)
		return (true);
	return (false);
}
