/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:21:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 15:42:43 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_ex(char *str, int size)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (size == 0)
		return (true);
	while (str[i] && i < size)
	{
		if (str[i] == 34)
			flag++;
		i++;
	}
	if (flag % 2 == 0)
		return (true);
	return (false);
}

char	**get_vars_content(char **var, char **env, char *str, int i)
{
	char	**vars;
	int		k;

	k = 0;
	vars = malloc(sizeof(char *) * (array_size(var) + 1));
	while (var[i])
	{
		while (str[k] && str[k] != '$')
		{
			k++;
			if (str[k] == '$' && str[k + 1] == '$')
				k += 2;
		}
		if (var[i][0] == '?' && var[i][1] == '\0')
			vars[i] = ft_itoa(g_signal.ret);
		else if (check_back_for_heredoc(str, k) == true)
			vars[i] = ft_strjoin("$", var[i]);
		else
			vars[i] = get_content(env, var[i]);
		i++;
		k++;
	}
	vars[i] = NULL;
	free_array(var);
	return (vars);
}

char	*join_vars(char **vars)
{
	char	*line;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = 0;
	j = 0;
	while (vars[i])
		size += ft_strlen(vars[i++]);
	line = malloc(sizeof(char) * (size + 1));
	i = 0;
	size = 0;
	while (vars[i])
	{
		j = 0;
		while (vars[i][j])
			line[size++] = vars[i][j++];
		i++;
	}
	line[size] = '\0';
	return (line);
}

char	*expand_variable(char *str, t_data *data)
{
	char	**var;
	char	**spleted_line;
	char	*line;
	t_line	line_data;

	line = NULL;
	if (dollar_is_in(str))
	{
		var = get_vars(str);
		var = get_vars_content(var, data->env, str, 0);
		spleted_line = ft_split_str(str);
		if (spleted_line == NULL)
			line = join_vars(var);
		else
		{
			line = get_final_line(spleted_line, var, str, &line_data);
			free_array(spleted_line);
		}
		free_array(var);
	}
	else
		return (str);
	free(str);
	return (line);
}

char	*check_expand(char *str, t_data *data)
{
	char	*new_str;

	new_str = expand_variable(str, data);
	return (new_str);
}
