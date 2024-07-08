/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:13 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/08 17:05:23 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_from_child(char **com)
{
	if (com[1] == NULL)
		exit(0);
	else if (is_numeric(com[1]) != 0)
		exit(2);
	else if (com[1] && com[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else
	{
		i = ft_atoi(com[1]);
		g_signal.ret = i;
		exit(i);
	}
	return ;
}

void	exit_myminishell(char **com, int flag)
{
	int	i;

	if (flag != 0)
		exit_from_child(com);
	if (com[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (is_numeric(com[1]) != 0)
	{
		printf("minishell: ");
		printf(com[1], 2);
		printf(": numeric argument required\n");
		exit(2);
	}
	else if (com[1] && com[2])
		printf("minishell: exit: too many arguments\n");
	else
	{
		i = ft_atoi(com[1]);
		printf("exit\n");
		g_signal.ret = i;
		exit(i);
	}
}

char	*get_my_path(t_env *list, char **com, bool flag, int i)
{
	char	**str;
	char	*path1;
	char	*mypath;
	char	*command_path;

	if (com[0][0] == '/' || com[0][0] == '.')
		return (ft_strdup(com[0]));
	path1 = findmyvar(list, list, "PATH", flag);
	if (!path1)
		return (NULL);
	str = ft_split(path1, ':');
	while (str[i])
	{
		command_path = ft_strjoin(str[i], "/", com[0]);
		if (access(command_path, X_OK) == 0)
		{
			mypath = command_path;
			break ;
		}
		free(command_path);
		i++;
	}
	free_array(str);
	return (mypath);
}
