/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/09 08:41:42 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_2d_size(char **vars, char **lines)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (vars[i])
		size += ft_strlen(vars[i++]);
	i = 0;
	while (lines[i])
		size += ft_strlen(lines[i++]);
	return (size);
}

int	array_size(char **var)
{
	int	i;

	i = 0;
	while (var[i])
		i++;
	return (i);
}

char	**linked_list_to_array(t_env *list)
{
	char	**array;
	t_env	*current;
	int		count;
	int		i;

	i = 0;
	count = count_nodes(list);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		exit(EXIT_FAILURE);
	current = list;
	while (i < count)
	{
		array[i] = ft_strdup(current->var_name);
		if (array[i] == NULL)
		{
			perror("strdup");
			free_array(array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
