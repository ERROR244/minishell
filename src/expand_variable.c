/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:21:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/10 10:14:54 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_ex(char *str, int size)
{
	int i;
	int flag;

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

int how_many_dollar_in(char *str)
{
	int i;
	int k;
	
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
		else if (str[i] == '$')
		{
			k++;
			i++;
		}
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
		if (cmd[j] == '$')
			var[k++] = grep_variable_name(cmd + j);
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
		size =  ft_strlen(str);
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

char	*get_final_line(char **lines, char **vars, char *cmd)
{
	char	*line;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	int		l = 0;
	int		size = 0;
	
	i = 0;
	while (vars[i])
		size += ft_strlen(vars[i++]);
	i = 0;
	while (lines[i])
		size += ft_strlen(lines[i++]);
	line = malloc(sizeof(char) * (size + 1));
	
	i = 0;
	k = 0;
	l = 0;
	size = 0;
	while (cmd[k++] == '$')
	{
		while (cmd[k] && ft_isalpha(cmd[k]))
			k++;
		j = 0;
		while (vars[i][j])
			line[size++] = vars[i][j++];
		i++;
	}
	k = 0;
	while (lines[k] || vars[i])
	{
		if (lines[k])
		{
			l = 0;
			while (lines[k][l])
				line[size++] = lines[k][l++];
			k++;
		}
		if (vars[i])
		{
			j = 0;
			while (vars[i][j])
			{
				line[size++] = vars[i][j++];
			}
			i++;
		}
	}
	line[size] = '\0';
	return (line);
}

char	**get_vars_content(char **var, char **env)
{
	char **vars;
	int i;

	i = 0;
	while (var[i])
		i++;
	vars = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (var[i])
	{
		if (var[i][0] == '?' && var[i][1] == '\0')
			vars[i] = ft_itoa(ret);
		else
			vars[i] = get_content(env, var[i]);
		// printf("%s \n", vars[i]);
		i++;
	}
	vars[i] = NULL;
	free_array(var);
	return (vars);
}

char	*join_vars(char **vars)
{
	char	*line;
	int i;
	int j;
	int size;

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
	char	*line = NULL;

	if (dollar_is_in(str))
	{
		var = get_vars(str);
		var = get_vars_content(var, data->env);
		// print_array(var);
		spleted_line = ft_split_str(str);
		if (spleted_line == NULL)
			line = join_vars(var);
		else
		{
			line = get_final_line(spleted_line, var, str);
			free_array(spleted_line);
		}
		free_array(var);
	}
    else
        return (str);
    free(str);
	// printf("%s \n", line);
    return (line);
}

char *check_tabs(char *str, int i, int j, t_data *data)
{
	char *new_str;
	int input_len;

    input_len = ft_strlen(str);
    new_str = (char *)malloc(input_len + 1);
    if (new_str == NULL)
		return (NULL);
    i = 0;
    while (j < input_len)
	{
        if (str[i] == '\t')
		{
            new_str[j++] = ' ';
			i++;
		}
        else
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
	new_str = expand_variable(new_str, data);
    return (new_str);
}
