/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/17 16:29:07 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_array(char **array)
{
    char **ptr = array;
    while (*ptr)
	{
        free(*ptr);
        ptr++;
    }
    free(array);
}

int check_for_in_out_put(t_cmds *cmds)
{
	
	if (cmds->token == Input)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
	}
	else if (cmds->token == Output)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
	}
	return (0);
}

int check_for_Append_heredoc(t_cmds *cmds)
{
	
	if (cmds->token == Append)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
	}
	else if (cmds->token == HereDoc)
	{
		if (!cmds->next || (cmds->next->token == Non && !cmds->next->next))
			return (errormsg(" 'newline'\n"));
	}
	return (0);
}

int	check_access(t_cmds *curr)
{
	if (curr->token == Infile)
		return (check_file(curr));
	else if (curr->token == OutFile)
		curr->data->outfile = open(curr->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (curr->token == AppendFile)
		curr->data->outfile = open(curr->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (curr->token == HereDocDel)
		return (check_if_NULL(curr->cmd));
	return (0);
}

int errors_managment(t_data *data, int i)
{
	t_cmds *curr;

	curr = data->lst;
	while (curr && i == 0)
	{
		if (curr->token == Pipe)
			i = check_for_pipe(curr);
		else if (curr->token == Output || curr->token == Input)
			i = check_for_in_out_put(curr);
		else if (curr->token == Append || curr->token == HereDoc)
			i = check_for_Append_heredoc(curr);
		else
			i = check_access(curr);
		curr = curr->next;
	}
	return (i);
}

char *get_line(char *str, int i)
{
	char *ptr;
	int j;
	
	j = 0;
	ptr = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		ptr[j] = str[j];
		j++;
	}
	ptr[j] = '\0';
	free(str);
	return (ptr);
}

int chack_if_prev_Non(char *str, int size)
{
	while (str[size])
	{
		while (size != 0 && str[size] == ' ')
			size--;
		if (size)
			return (1);
	}
	return (0);
}

char *check_line(char *str)
{
	char *ptr;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == '|')
		i++;
	while (str[i])
	{
		while (str[i] == '|')
		{
			i++;
			j++;
		}
		if ((j == 2 || !str[i]) && chack_if_prev_Non(str, i) == 0)
			break ;
		j = 0;
		i++;
	}
	if (j != 2)
		return (str);
	ptr = get_line(str, i - j);
	return (ptr);
}

// t_cmds	*init_the_tree(t_cmds *cmds, int size)
// {
// 	t_cmds *root;
// 	t_cmds *tmp;
	
// 	if (size == 1)
// 	{
// 		cmds->left = NULL;
// 		cmds->right = NULL;
// 		return (cmds);
// 	}
// 	else if (size == 2)
// 	{
// 		root = cmds->next;
// 		cmds->left = cmds;
// 		cmds->right = NULL;
// 		return (root);
// 	}
// 	else
// 	{
// 		root = cmds->next;
// 		cmds->left = cmds;
// 		cmds->right = cmds->next->next;
// 		return (root);
// 	}
// }

void parsing(t_data *data)
{
    // t_cmds *root;
    t_cmds *lst;
    t_cmds *cur;
	char **cmds;
	int ret;
	int i;

	i = -1;
	data->line = check_line(data->line);
	cmds = ft_split_msh(data->line);
	lst = NULL;
	while (cmds[++i])
	{
		if (cmdcheck(cmds[i]) == 0)
			cmds[i] = rm_spaces(cmds[i]);
	}
	
	
	// for (int i = 0; cmds[i]; i++)
	// 	printf(":%s:\n", cmds[i]);
    
	
	get_list(cmds, i, &lst, data);
	init_tokens(lst, 0, lst);
	data->lst = lst;
	data->cmds = cmds;
	ret = errors_managment(data, 0);

	if (ret != 0 || 1)
	{
		// root = init_the_tree(lst, i);
		
		// preOrder(root);

		char str[100][100] = { "Cmd", "AppendFile",
								"HereDocDel", "Infile",
								"OutFile", "Input",
								"Output", "Append",
								"HereDoc", "Pipe",
								"Non" };
		while (lst)
		{
			if (lst->cmd == NULL)
				printf("cmds->cmd == NULL");
			else
				printf("%s---->%s \n", lst->cmd, str[lst->token]);
			if (!lst->next)
				break;
			lst = lst->next;
		}
		
		// printf("\n");
		
		while (lst)
		{
			if (!lst->prev)
				break;
			lst = lst->prev;
		}

		// exe
		// executing(root);
	}
	
	close_used_files(data);


	cur = lst;		// free
	
	
	while (cur)
	{
		free(cur->cmd);
		free(cur->flags);
		cur = cur->next;
	}
	
	lstclear(&lst);
	free_array(cmds);
}
