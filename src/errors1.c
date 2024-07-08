/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/08 14:19:38 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_env_if_plus(t_env *index, char *export)
{
	char *tmp;

	tmp = index->var_name;
	if (tmp[ft_strlen(tmp) - 1] != '=' && check_eq(tmp) == true)
		index->var_name = ft_strjoin3(tmp, '=', export);
	else
		index->var_name = ft_strjoin(tmp, export);
	free(tmp);
}

int	ft_strcmp_for_heredoc(char *s1, char *s2)
{
	char	*str;
	int		k;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = get_string(ft_strdup(s2), 0, 0, get_size(s2));
	while (s1[i] == str[i] && s1[i] != '\0' && str[i] != '\0')
		i++;
	k = s1[i] - str[i];
	free(str);
	return (k);
}

int	heredoc(t_cmds	*head, t_cmds	*curr, int i)
{
	int		heredoc_num;

	heredoc_num = 0;
	while (curr)
	{
		if (heredoc_num > 16)
		{
			ft_putstr_fd("minishell: maximum here-document count exceeded\n",
				2);
			exit(2);
		}
		if (curr->token == HereDoc)
			heredoc_num++;
		curr = curr->next;
	}
	while (head && i != 130)
	{
		if (head->token == HereDocDel)
			i = open_heredoc(head, 0, 0, true);
		head = head->next;
	}
	return (i);
}

int	errors_managment(t_data *data, int i)
{
	t_cmds	*curr;
	t_cmds	*head;

	curr = data->lst;
	head = curr;
	while (curr && i == 0)
	{
		if (curr->token == Pipe)
			i = check_for_pipe(curr);
		else if (curr->token == Output || curr->token == Input)
			i = check_for_in_out_put(curr);
		else if (curr->token == Append || curr->token == HereDoc)
			i = check_for_append_heredoc(curr);
		curr = curr->next;
	}
	return (heredoc(head, head, i));
}

int	cmdcheck(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
