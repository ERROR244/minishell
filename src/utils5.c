/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 19:04:33 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	how_many_dollar_in(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str && str[i])
	{
		if (str[i] == 39 && check_ex(str, i) == true)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		else if (str[i] == '$' && str[i + 1] != '$')
		{
			k++;
			i++;
		}
		else if (str[i] == '$' && str[i + 1] == '$')
			i++;
		if (str[i])
			i++;
	}
	return (k + 1);
}

char	**get_vars(char *cmd)
{
	char	**var;
	int		k;
	int		j;

	var = malloc(sizeof(char *) * how_many_dollar_in(cmd));
	k = 0;
	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == 39 && check_ex(cmd, j) == true)
		{
			j++;
			while (cmd[j] && cmd[j] != 39)
				j++;
		}
		if (cmd[j] == '$' && cmd[j + 1] != '$')
			var[k++] = grep_variable_name(cmd + j);
		else if (cmd[j] == '$' && cmd[j + 1] == '$')
			j++;
		j++;
	}
	var[k] = NULL;
	return (var);
}

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
	int i;
	int tpos;

	i = 0;
	tpos = pos;
	if (ptr)
	{
		while (ptr[i])
			line[tpos++] = ptr[i++];
	}
	return (tpos);
}

char	*get_final_line(char **lines, char **vars, char *cmd, char	*line)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		pos;

	j = 0;
	i = 0;
	k = 0;
	l = 0;
	int size = 0;
	pos = 0;
	line = malloc(sizeof(char) * (get_2d_size(vars, lines) + 1));
	while (cmd[size])
	{
		if (cmd[size] != '$' && lines[k])
		{
			pos = fill_in(line, lines[k++], pos);
			while (cmd[size] && cmd[size] != '$')
				size++;
		}
		if (cmd[size] == '$' && vars[i])
		{
			pos = fill_in(line, vars[i++], pos);
			if (cmd[size + 1] == '?')
				size += 2;
			else
			{
				size++;
				while (cmd[size] && ft_isalnum(cmd[size]) == 1)
					size++;
			}
		}
	}
	line[pos] = '\0';
	return (line);
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
