/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:35 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/09 08:31:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_env_after_export(t_env *list, char **export, char c,
			bool export_flag)
{
	t_env	*index;

	index = findmyindex(list, export[0]);
	if (index)
	{
		if (c == '+')
			set_env_if_plus(index, export[1]);
		else
		{
			if (export[1] != NULL || export_flag == true)
				free(index->var_name);
			if (export[1] != NULL)
				index->var_name = ft_strjoin3(export[0], '=', export[1]);
			else if (export_flag == true)
				index->var_name = ft_strjoin3(export[0], '=', "");
		}
		return ;
	}
	list = env_last(list);
	list->next = env_new(list, ft_strjoin3(export[0], '=', export[1]));
}

void	set_env_after_cd(t_env *list, char *key, char *value)
{
	t_env	*index;
	t_env	*node;
	char	*tmp;

	index = findmyindex(list, key);
	if (index && (ft_strcmp(key, "OLDPWD") == 0 || ft_strcmp(key, "PWD") == 0))
	{
		free(index->var_name);
		index->var_name = ft_strjoin(key, "=");
		if (value)
		{
			tmp = index->var_name;
			index->var_name = ft_strjoin(index->var_name, value);
			free(tmp);
		}
	}
	else if (!index && (ft_strcmp(key, "PWD") == 0 || ft_strcmp(key,
				"OLDPWD") == 0))
	{
		node = env_new(list, ft_strjoin3(key, '=', value));
		list = env_last(list);
		list->next = node;
	}
}

void	change_mydir(t_env *list, char *path)
{
	char	*cur;
	char	buffer[PATH_MAX];

	cur = findmyvar(list, list, "PWD", false);
	if (chdir(path) != 0)
		perror("cd");
	else
	{
		set_env_after_cd(list, "OLDPWD", cur);
		set_env_after_cd(list, "PWD", getcwd(buffer, PATH_MAX));
	}
}

char	*findmyvar(t_env *list, t_env *head, char *va, bool flag)
{
	char	**vale;

	while (list)
	{
		vale = ft_split(list->var_name, '=');
		if (ft_strcmp(vale[0], va) == 0)
		{
			free_array(vale);
			return (ft_strchr(list->var_name, '=') + 1);
		}
		free_array(vale);
		if (!list->next)
			break ;
		list = list->next;
	}
	while (head)
	{
		if (ft_strncmp(head->var_name, "path", 3) == 0)
			return (NULL);
		head = head->next;
	}
	if (ft_strncmp(va, "PATH", 3) == 0 && flag == true)
		return ("/usr/bin");
	return (NULL);
}

int	morethan2arg(char **com)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (com[i])
	{
		i++;
		counter++;
	}
	return (counter);
}
