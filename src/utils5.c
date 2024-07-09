/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/09 14:35:11 by ksohail-         ###   ########.fr       */
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

void	cmd_check(char **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == 39)
		{
			i++;
			while ((*cmd)[i] && (*cmd)[i] != 39)
			{
				if ((*cmd)[i] == '$')
					(*cmd)[i] = '1';
				i++;
			}
		}
		else
			i++;
	}
}

void	init_line_data(t_line *line_data, char **lines, char **vars, char **cmd)
{
	line_data->i = 0;
	line_data->k = 0;
	line_data->size = 0;
	line_data->pos = 0;
	line_data->line = malloc(sizeof(char) * (get_2d_size(vars, lines) + 1));
	cmd_check(cmd);
}

char	*get_final_line(char **lines, char **vars, char *cmd, t_line *data)
{
	init_line_data(data, lines, vars, &cmd);
	while (cmd[data->size])
	{
		if ((cmd[data->size] != '$' || cmd[data->size + 1] != '$')
			&& lines[data->k])
		{
			data->pos = fill_in(data->line, lines[data->k++], data->pos);
			while (cmd[data->size] && cmd[data->size] != '$')
				data->size++;
		}
		if (cmd[data->size] == '$' && vars[data->i] && vars[data->i][0] != '\0')
		{
			data->pos = fill_in(data->line, vars[data->i++], data->pos);
			data->size++;
			if (cmd[data->size] == '?')
				data->size++;
			else
				while (cmd[data->size] && ft_isalnum(cmd[data->size]) == 1)
					data->size++;
		}
		else if (cmd[data->size])
			data->size++;
	}
	data->line[data->pos] = '\0';
	return (data->line);
}
