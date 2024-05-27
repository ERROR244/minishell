/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/27 11:54:09 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t get_size(char *str)
{
	size_t	k;
	size_t	i;
	char	tmp;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i];
			i++;
			while (str[i] != tmp)
				i++;
			k += 2;
		}
		i++;
	}
	return (i - k);
}

static char	*get_string(char *str, size_t i, size_t k, size_t size)
{
	char	*ptr;
	char	tmp;

	if (size == ft_strlen(str))
		return (str);
	ptr = malloc(sizeof(char) * (size + 1));
	while (k < size)
	{
		while (str[i] == 39 || str[i] == 34)
		{
			tmp = str[i++];
			while (str[i] != tmp)
			{
				ptr[k++] = str[i++];
			}
			i++;
		}
		if (k == size)
			break ;
		ptr[k++] = str[i++];
	}
	ptr[k] = '\0';
	free(str);
	return (ptr);
}

int how_many_dollar_in(char *str)
{
	int i;
	int k;
	
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			k++;
			i++;
		}
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
	// printf(":%s:\n", line);
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
		vars[i] = get_content(env, var[i]);
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

void	expand_variable(t_cmds *cmds)
{
	char	**var;
	char	**spleted_line;
	char	*line;
	int		i;

	while (cmds)
	{
		i = 0;
		// printf("HERE\n");
		while (cmds->cmd[i])
		{
			if (dollar_is_in(cmds->cmd[i]))
			{
				var = get_vars(cmds->cmd[i]);
				var = get_vars_content(var, cmds->data->env);
				spleted_line = ft_split_str(cmds->cmd[i]);
				if (spleted_line == NULL)
				{
					free(cmds->cmd[i]);
					cmds->cmd[i] = join_vars(var);
				}
				else
				{
					line = get_final_line(spleted_line, var, cmds->cmd[i]);
					free(cmds->cmd[i]);
					cmds->cmd[i] = line;
					// for (int i = 0; spleted_line[i]; i++)
					// 	printf (":%s:\n", spleted_line[i]);
					// printf("\n");
					// for (int i = 0; var[i]; i++)
					// 	printf (":%s:\n", var[i]);
					// printf("\n");
					// free(var);
					// free(spleted_line);
					free_array(spleted_line);
				}
				free_array(var);
			}
			// else
				// free(cmds->cmd[i]);			//	why i add this??
			i++;
		}
		cmds = cmds->next;
	}
}

void	remove_quotes(t_cmds *lst)
{
	int i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			if (lst->cmd[i] != NULL)
				lst->cmd[i] = get_string(lst->cmd[i], 0, 0, get_size(lst->cmd[i]));
			i++;
		}
		// if (ft_strcmp("echo", lst->cmd[0]) == 0)
		expand_variable(lst);
		lst = lst->next;
	}
}
