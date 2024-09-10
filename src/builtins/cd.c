/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:35 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 14:49:16 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_if_plus(t_env *index, char *export)
{
	char	*tmp;

	tmp = index->var_name;
	if (tmp[ft_strlen(tmp) - 1] != '=' && check_eq(tmp) == true)
		index->var_name = ft_strjoin3(tmp, '=', export);
	else
		index->var_name = ft_strjoin(tmp, export);
	free(tmp);
}

void	set_env_after_cd(t_env *list, char *key, char *value)
{
	t_env	*index;
	t_env	*node;
	char	*tmp;

	index = find_env_var_index(list, key);
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

void	change_my_dir(t_env *list, char *path)
{
	char	*cur;
	char	buffer[PATH_MAX];

	cur = find_env_var(list, list, "PWD", false);
	if (path[0] == '\0')
		return ;
	if (chdir(path) != 0)
		perror("cd");
	else
	{
		set_env_after_cd(list, "OLDPWD", cur);
		set_env_after_cd(list, "PWD", getcwd(buffer, PATH_MAX));
	}
}

char	*find_env_var(t_env *list, t_env *head, char *va, bool flag)
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

int	more_then_two_arg(char **com)
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

void	my_cd(t_env *list, char **com)
{
	char	*myhome;
	int		counter;

	counter = more_then_two_arg(com);
	if (counter > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	myhome = find_env_var(list, list, "HOME", false);
	if (com[1] == NULL || com[1][0] == '~')
	{
		if (!myhome)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else
			change_my_dir(list, myhome);
	}
	else
		change_my_dir(list, com[1]);
}
