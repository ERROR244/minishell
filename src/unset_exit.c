/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:13 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 10:09:31 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_myminishell(char **com, int flag)
{
	int	i;

	if (flag != 0)
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

char	*join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*concatenated;
	size_t	j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	concatenated = (char *)malloc((len1 + len2) * sizeof(char) + 1);
	if (concatenated == NULL)
		return (NULL);
	while (len1 > i)
	{
		concatenated[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		concatenated[i++] = s2[j++];
	concatenated[len1 + len2] = '\0';
	return (concatenated);
}

char	*get_my_path(t_env *list, char **com, bool flag)
{
	char	**str;
	char	*path1;
	int		i;
	char	*mypath;
	char	*joiner;
	char	*command_path;

	if (com[0][0] == '/' || com[0][0] == '.')
		return (ft_strdup(com[0]));
	path1 = findmyvar(list, list, "PATH", flag);
	if (!path1)
		return (NULL);
	str = ft_split(path1, ':');
	if (!str)
		return (NULL);
	i = 0;
	mypath = (NULL);
	while (str[i])
	{
		joiner = join(str[i], "/");
		command_path = ft_strjoin(joiner, com[0]);
		free(joiner);
		if (access(command_path, X_OK) == 0)
		{
			mypath = command_path;
			break ;
		}
		free(command_path);
		i++;
	}
	free_array(str);
	if (!mypath)
		return (NULL);
	return (mypath);
}
