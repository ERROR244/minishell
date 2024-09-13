/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:48:23 by error01           #+#    #+#             */
/*   Updated: 2024/07/12 15:36:48 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	check_for_in_out_put(t_cmds *cmds)
{
	if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
		return (error_msg(" 'newline'\n"));
	else if (cmds->next && cmds->next->next && cmds->next->token == Pipe
		&& cmds->next->next->token == Pipe)
		return (error_msg_v2(cmds->next->cmd[0]));
	else if (cmds->next && cmds->next->operation == Operation)
		return (error_msg_v1(cmds->next->cmd[0]));
	else if (cmds->prev && cmds->prev->token == Non && cmds->prev->prev
		&& cmds->prev->prev->token != Pipe)
		return (error_msg_v1(cmds->cmd[0]));
	return (0);
}

int	check_for_append_heredoc(t_cmds *cmds)
{
	if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
		return (error_msg(" 'newline'\n"));
	else if (cmds->prev && cmds->prev->token == Non && cmds->prev->prev
		&& cmds->prev->prev->token != Pipe)
		return (error_msg_v1(cmds->cmd[0]));
	else if (cmds->next && cmds->next->next && cmds->next->token == Pipe
		&& cmds->next->next->token == Pipe)
		return (error_msg_v2(cmds->next->cmd[0]));
	else if (cmds->next && cmds->next->operation == Operation)
		return (error_msg_v1(cmds->next->cmd[0]));
	return (0);
}

char	**get_file_name(char *str)
{
	char	**ptr;
	int		size;
	int		i;

	size = 0;
	i = 0;
	ptr = ft_malloc(sizeof(char *) * (3), g_signal.node);
	while (str[size] && str[size] != ' ' && str[size] != '	')
		size++;
	ptr[0] = ft_malloc(sizeof(char) * (size + 1), g_signal.node);
	ft_strlcpy(ptr[0], str, size + 1);
	if (!str[size])
	{
		ptr[1] = NULL;
		return (ptr);
	}
	i = 0;
	while (str[i])
		i++;
	ptr[1] = ft_malloc(sizeof(char) * (i - size + 1), g_signal.node);
	ft_strlcpy(ptr[1], str + size, ft_strlen(str + size) + 1);
	ptr[2] = NULL;
	return (ptr);
}

char	*rm_spaces(char *str)
{
	int		i;
	int		k;
	int		l;
	char	*ptr;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	l = i;
	k = i;
	while (str[i++])
		l++;
	i--;
	while (str[i] == ' ' || str[i] == '	')
	{
		i--;
		l--;
	}
	ptr = ft_malloc(sizeof(char) * (l - k + 1), g_signal.node);
	i = 0;
	while (k < l)
		ptr[i++] = str[k++];
	ptr[i] = '\0';
	free(str);
	return (ptr);
}
