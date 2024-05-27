/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:47:27 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/27 09:43:13 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
