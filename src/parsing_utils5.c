/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:57:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/24 17:14:27 by ksohail-         ###   ########.fr       */
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
		if (ft_strcmp("echo", lst->cmd[0]) == 0)
			expand_variable(lst);
		lst = lst->next;
	}
}

char	*is_the_variable_in(char **env, char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (str == NULL)
		return (NULL);
	while (env[i])
	{
		ptr = ft_strnstr(env[i], str, ft_strlen(str));
		if (ptr != NULL)
			return (ptr);
		i++;
	}
	return (NULL);
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

// line1	var1
						// line2 = line1+var1+line2
// line2	var2
						// line3 = line2+var2+line3
// line3	var3
						// line4 = line3+var3+line4				//	algo.
// line4	var4
						// line5 = line4+var4+line5
// line5	var5
						// line6 = line5+var5+line6
// line6	var6
						// line6 = line6+var6

						
char	*get_final_line(char **lines, char **vars)
{
	char	*line;
	char	*tmp;
	int		i = 0;
	int		j = 0;

	// line = ft_strjoin(lines[0], vars[0]);
	line = NULL;
	
	while (lines[i] || vars[j])
	{
		if (lines[i])
		{
			tmp = ft_strjoin(line, lines[i]);
			if (!line)
				free(line);
			line = tmp;
			i++;
		}
		if (vars[j])
		{
			tmp = ft_strjoin(line, vars[j]);
			if (!line)
				free(line);
			line = tmp;
			j++;
		}
	}


	
	return (line);
}

void	expand_variable(t_cmds *cmds)
{
	char	**var;
	char	**spleted_line;
	char	*line;
	int		i;
	int		j;
	int		k;

	while (cmds)
	{
		i = 1;
		while (cmds->cmd[i])
		{
			if (dollar_is_in(cmds->cmd[i]))
			{
				var = malloc(sizeof(char *) * how_many_dollar_in(cmds->cmd[i]));
				k = 0;
				j = 0;
				while (cmds->cmd[i][j])
				{
					if (cmds->cmd[i][j] == '$')
					{
						var[k] = grep_variable_name(cmds->cmd[i] + j);
						k++;
					}
					j++;
				}
				var[k] = NULL;
				spleted_line = ft_split_str(cmds->cmd[i]);

				
				line = get_final_line(spleted_line, var);		//	working on
				
				free(cmds->cmd[i]);
				cmds->cmd[i] = line;
				printf("%s \n", cmds->cmd[i]);
				// for (int t = 0; var[t]; t++)
				// 	printf("HERE is N = %d -> %s \n", t, var[t]);
				free_array(var);
				free_array(spleted_line);
			}
			else
				free(cmds->cmd[i]);
			i++;
		}
		cmds = cmds->next;
	}
	
}
