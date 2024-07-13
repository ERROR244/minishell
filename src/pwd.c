/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:40:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/13 09:34:39 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_cd(t_env *list, char **com)
{
	char	*myhome;
	int		counter;

	counter = morethan2arg(com);
	if (counter > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	myhome = findmyvar(list, list, "HOME", false);
	if (com[1] == NULL || com[1][0] == '~')
	{
		if (!myhome)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else
			change_mydir(list, myhome);
	}
	else
		change_mydir(list, com[1]);
}

void	mypwd(t_env *env)
{
	char	buffer[PATH_MAX];
	char	*cur;
	char	*str;

	cur = getcwd(buffer, PATH_MAX);
	if (cur)
	{
		ft_putstr_fd(cur, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		str = findmyvar(env, env, "PWD", false);
		ft_putstr_fd(str, 1);
		ft_putchar_fd('\n', 1);
	}
}

t_env	*remove_node(t_env *head, t_env *node_to_remove)
{
	if (!head || !node_to_remove)
		return (head);
	if (node_to_remove == head)
	{
		head = node_to_remove->next;
		if (head)
			head->prev = NULL;
		free(node_to_remove->var_name);
		free(node_to_remove);
		return (head);
	}
	if (node_to_remove->prev)
		node_to_remove->prev->next = node_to_remove->next;
	if (node_to_remove->next)
		node_to_remove->next->prev = node_to_remove->prev;
	free(node_to_remove->var_name);
	free(node_to_remove);
	return (head);
}

t_env	*unset_env(t_env *list, char **com, t_data *data)
{
	t_env	*index;
	int		i;

	i = 0;
	index = NULL;
	while (com[i])
	{
		if (is_it_inside(com[i]) == false)
		{
			if (data->path_flag == true && ft_strcmp(com[i], "PATH") == 0)
				data->path_flag = false;
			index = findmyindex(list, com[i]);
			if (index)
				list = remove_node(list, index);
		}
		i++;
	}
	return (list);
}

int	is_numeric(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		str++;
	}
	return (0);
}
