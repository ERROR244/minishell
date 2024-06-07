/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/07 17:43:47 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// executing_command
int execute_command(t_env *list, t_command *command, t_data *data, int index)
{
    char *path;

    if (!command->cmd)
        return (-1);
    char **com = command->cmd;
    if (com[0][0] == '\0')
    {
        ft_putstr_fd("minishell: command '' not found\n", 2);
        return (127);
    }
    path = get_my_path(list, com);
    if(path == NULL)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(com[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        return (127);
    }
    data->pid[index] = fork();
    if (data->pid[index] == 0)
    {
        if (command->prev && !command->infile)
        {
            dup2(data->fd_in, STDIN_FILENO);
            close(data->fd_in);
        }
    	if (command->next && !command->outfile && !command->appendfile)
            dup2(data->fd[1], STDOUT_FILENO);
        close(data->fd[0]);
        close(data->fd[1]);
        execve(path, com, data->env);
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(com[0], 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        exit(-1);
    }
    else if (data->pid[index] < 0)
    {
        free(path);
        return (-1);
    }
    if (path)
        free(path);
    return (0);
}

int get_files_num(t_slist *list)
{
	int i;
	int size;

	size = 0;
	while (list)
	{
		i = 0;
		while (list && list->cmd[i])
		{
			size++;
			i++;
		}
		list = list->next;
	}
	return (size);
}

void	ft_close(int *fd)
{
	int i = 0;

	while (fd && fd[i] != -11)
	{
		if (fd[i] == -1)
			break;
		close(fd[i]);
		i++;
	}
	if (fd)
		free(fd);
}

int *ft_open(t_slist *list, t_token token)
{
	int *fd;
	int i;
	int j;
	int size;

	size = get_files_num(list);
	fd = malloc((size + 1) * (sizeof(int)));
	fd[size] = -11;
	j = 0;
    while (list)
	{
		i = 0;
		while (list && list->cmd[i])
		{
			if (token == Infile)
				fd[j] = open(list->cmd[i], O_RDONLY);
			else if (token == OutFile)
				fd[j] = open(list->cmd[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (token == AppendFile)
				fd[j] = open(list->cmd[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
			
			if (fd[j] == -1)
			{
				ft_close(fd);
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(list->cmd[i], 2);
				ft_putstr_fd(": ", 2);
                ft_putstr_fd(strerror(errno), 2);
                ft_putchar_fd('\n', 2);
				return (NULL);
			}
            else
            {
			    if (token == Infile)
            	    dup2(fd[j], STDIN_FILENO);
    			else if (token == OutFile || token == AppendFile)
            	    dup2(fd[j], STDOUT_FILENO);
            }
			
			j++;
			i++;
		}
		list = list->next;
	}
	return (fd);
}

int get_last_index(int *fd)
{
	int i;

	i = 0;
	while (fd[i] != -11)
	{
		if (fd[i] == -1)
			return (i);
		i++;
	}
	return (i - 1);
}

void hand_the_redirectionin(t_command *lst, int in, int out)
{
    int *filein  = NULL;
    int *fileout = NULL;

    while (lst)
    {
        if(lst->infile != NULL)
        {
            filein = ft_open(lst->infile, Infile);
			
            if(!filein)
			{
	        	close(in);
				return ;
			}
        }
        if(lst->outfile || lst->appendfile)
        {
            if (lst->appendfile)
                fileout = ft_open(lst->appendfile, AppendFile);
            else
                fileout = ft_open(lst->outfile, OutFile);

            if(!fileout)
			{
        		close(out);
				return ;
			}
        }
        if (!lst->next)
            break ;
        lst = lst->next;
    }
    while (lst)
    {
        if (!lst->prev)
            break ;
        lst = lst->prev;
    }
    ft_close(filein);
    ft_close(fileout);
}

int get_command_size(t_command *command)
{
    int size;

    size = 0;
    while (command)
    {
        command = command->next;
        size++;
    }
    return (size);
}

int	wait_pid(int *pid, int status, int cmd_num)
{
	int	i;

	i = cmd_num;
	status = 0;
	waitpid(pid[i--], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (i >= 0)
		waitpid(pid[i--], 0, 0);
	return (status);
}


int executing(t_data *data)
{
    t_command   *list;
    int         ret;
    int         out = dup(STDOUT_FILENO);
    int         in = dup(STDIN_FILENO);


    list = data->list;
    data->fd_in = STDIN_FILENO;
    data->pid = malloc(sizeof(int) * (get_command_size(list) + 1));
    data->k = 0;
    while (list)
    {
        if (list->next)
        {
            if (pipe(data->fd) == -1)
                break ;
        }
        if(!list || (list->cmd && list->cmd[0][0] == '\n'))
            return (2);
        if(list->infile || list->outfile || list->appendfile)
            hand_the_redirectionin(list, in, out);
        if(list->cmd && ft_strcmp(list->cmd[0], "cd") == 0)   
            my_cd(data->list_env->next, list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "pwd") == 0)
            mypwd(data->list_env->next);
        else if(list->cmd && ft_strcmp(list->cmd[0], "env") == 0 && list->cmd[1] == NULL)
            printmyenv(data->list_env->next);
        else if(list->cmd && ft_strcmp(list->cmd[0], "export") == 0)
            export(data->list_env->next, list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "unset") == 0)
            data->list_env = unset_env(data->list_env, list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "exit") == 0)
            exit_myminishell(list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "echo") == 0)
                ft_echo(list->cmd + 1, true, 0);
        else
            ret = execute_command(data->list_env->next, list, data, data->k++);
        if (list->infile)
            dup2(in, STDIN_FILENO);
        if (list->outfile || list->appendfile)
            dup2(out, STDOUT_FILENO);
        if (list->next && !list->outfile && !list->appendfile)
            close(data->fd[1]);
        if (list->prev && !list->infile)
            close(data->fd_in);
        data->fd_in = data->fd[0];
        list = list->next;
    }
    if (ret == 0)
            ret = wait_pid(data->pid, 0, data->k);
	free(data->pid);
    return (ret);
}
