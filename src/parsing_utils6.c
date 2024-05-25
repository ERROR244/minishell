/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:47:27 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/25 11:35:36 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	dollar_is_in(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
			k++;
		i++;
	}
	return (k);
}

char	*grep_variable_name(char *line)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	if (!line)
		return (NULL);
	j = ++i;
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
