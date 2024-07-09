/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/09 08:36:22 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_content(char **env, char *str)
{
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (str == NULL)
		return (NULL);
	while (env[i])
	{
		size = ft_strlen(str);
		ptr = ft_strnstr(env[i], str, size);
		if (ptr != NULL)
		{
			if (*(ptr + size) == '=')
				return (ft_strdup(ptr + size + 1));
			else
				return (ft_strdup(""));
		}
		i++;
	}
	return (ft_strdup(""));
}

int	fill_in(char *line, char *ptr, int pos)
{
	int	i;
	int	tpos;

	i = 0;
	tpos = pos;
	if (ptr)
	{
		while (ptr[i])
			line[tpos++] = ptr[i++];
	}
	return (tpos);
}

void	init_line_data(t_line *line_data, char **lines, char **vars)
{
	line_data->i = 0;
	line_data->k = 0;
	line_data->size = 0;
	line_data->pos = 0;
	line_data->line = malloc(sizeof(char) * (get_2d_size(vars, lines) + 1));
}

char	*get_final_line(char **lines, char **vars, char *cmd, t_line *l_data)
{
	init_line_data(l_data, lines, vars);
	while (cmd[l_data->size])
	{
		if (cmd[l_data->size] != '$' && lines[l_data->k])
		{
			l_data->pos = fill_in(l_data->line, lines[l_data->k++],
					l_data->pos);
			while (cmd[l_data->size] && cmd[l_data->size] != '$')
				l_data->size++;
		}
		if (cmd[l_data->size] == '$' && vars[l_data->i])
		{
			l_data->pos = fill_in(l_data->line, vars[l_data->i++], l_data->pos);
			if (cmd[l_data->size + 1] == '?')
				l_data->size += 2;
			else
			{
				l_data->size++;
				while (cmd[l_data->size] && ft_isalnum(cmd[l_data->size]) == 1)
					l_data->size++;
			}
		}
	}
	l_data->line[l_data->pos] = '\0';
	return (l_data->line);
}

bool	check_back_for_heredoc(char *str, int index)
{
	if (index < 0 || !str[index])
		return (false);
	index--;
	while (index >= 0 && str[index] == ' ')
		index--;
	if (index >= 1 && str[index] == '<')
	{
		index--;
		if (index >= 0 && str[index] == '<')
			return (true);
	}
	return (false);
}
