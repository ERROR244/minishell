/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 08:55:10 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_files_num(t_slist *list)
{
	int size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

void	ft_ft_close(int *fd)
{
	int i = 0;

	while (fd && fd[i] != -11)
	{
		if (fd[i] == -1)
			break;
		ft_close(fd[i], "fd[i]");
		i++;
	}
	if (fd)
		free(fd);
}

int *ft_open(t_slist *list)
{
	int *fd;
	int j;
	int size;

	size = get_files_num(list);
	fd = malloc((size + 1) * (sizeof(int)));
	fd[size] = -11;
	j = 0;
    while (list)
	{
        if (list->token == Infile)
			fd[j] = open(list->cmd, O_RDONLY);
		else if (list->token == OutFile)
			fd[j] = open(list->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (list->token == AppendFile)
			fd[j] = open(list->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
		
		if (fd[j] == -1)
		{
			ft_ft_close(fd);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(list->cmd, 2);
			ft_putstr_fd(": ", 2);
            ft_putstr_fd(strerror(errno), 2);
            ft_putchar_fd('\n', 2);
			return (NULL);
		}
        if (list->token == Infile)
            dup2(fd[j], STDIN_FILENO);
        else if (list->token == OutFile || list->token == AppendFile)
            dup2(fd[j], STDOUT_FILENO);
		j++;
		list = list->next;
	}
	return (fd);
}

int hand_the_redirectionin(t_command *lst)
{
    int *filein  = NULL;
    int *fileout = NULL;

    if(lst->infile != NULL)
    {
        filein = ft_open(lst->infile);
        if(!filein)
			return (1);
    }
    if(lst->outfile)
    {
        if (lst->outfile)
            fileout = ft_open(lst->outfile);
        if(!fileout)
			return (1);
    }
    if (filein)
        ft_ft_close(filein);
    if (fileout)
        ft_ft_close(fileout);
    return (0);
}