/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/09 15:00:09 by ksohail-         ###   ########.fr       */
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
        if (data->flag != true)
            return (0);
        ft_putstr_fd("minishell: command '' not found\n", 2);
        return (127);
    }
    path = get_my_path(list, com, data->path_flag);
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
        if (command->next)
        {
            ft_close(data->fd[1], strerror(errno));
            ft_close(data->fd[0], strerror(errno));
        }
	    free(data->pid);
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

int ft_open(t_slist *list, t_token token)
{
	int fd;

	if (token == Infile)
		fd = open(list->cmd[0], O_RDONLY);
	else if (token == OutFile)
		fd = open(list->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(list->cmd[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(list->cmd[0], 2);
		ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putchar_fd('\n', 2);
		return (-1);
	}
    else
    {
	    if (token == Infile)
    	    dup2(fd, STDIN_FILENO);
    	else if (token == OutFile || token == AppendFile)
    	    dup2(fd, STDOUT_FILENO);
    }
    ft_close(fd, strerror(errno));
	return (fd);
}

int hand_the_redirectionin(t_command *lst, int in, int out)
{
    int filein;
    int fileout;

    while (lst)
    {
        if(lst->infile)
        {
            filein = ft_open(lst->infile, Infile);
			
            if(filein == -1)
			{
	        	ft_close(in, strerror(errno));
				return (1);
			}
        }
        if(lst->outfile || lst->appendfile)
        {
            if (lst->appendfile)
                fileout = ft_open(lst->appendfile, AppendFile);
            else
                fileout = ft_open(lst->outfile, OutFile);

            if(fileout == -1)
			{
        		ft_close(out, strerror(errno));
				return (1);
			}
        }
        if (!lst->next)
            break ;
        lst = lst->next;
    }
    return (0);
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

int	wait_pid(int *pid, int cmd_num)
{
	int	i;
    int status;

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
    int         out = dup(STDOUT_FILENO);
    int         in = dup(STDIN_FILENO);
    int         write_in;

    list = data->list;
    data->pid = malloc(sizeof(int) * (get_command_size(list) + 1));
    data->k = 0;
    data->fd_in = STDIN_FILENO;
    while (list)
    {
        write_in = STDOUT_FILENO;
        if (list->next)
        {
            if (pipe(data->fd) == -1)
                break ;
            write_in = data->fd[1];
        }
        if(!list || (list->cmd && list->cmd[0][0] == '\n'))
        {
            free(data->pid);
            return (2);
        }
        if(list->infile || list->outfile || list->appendfile)
            ret = hand_the_redirectionin(list, in, out);
        if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "cd") == 0)   
            my_cd(data->list_env, list->cmd);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "pwd") == 0)
            mypwd(data->list_env, write_in);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "env") == 0 && list->cmd[1] == NULL)
            printmyenv(data->list_env, write_in);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "export") == 0)
            export(data->list_env, list->cmd, write_in);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "unset") == 0)
            data->list_env = unset_env(data->list_env, list->cmd, data);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "exit") == 0)
            exit_myminishell(list->cmd);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "echo") == 0)
                ft_echo(list->cmd + 1, true, 0, write_in);
        else if (ret == 0)
            ret = execute_command(data->list_env, list, data, data->k++);
        if (ret == 0 && list->infile)
            dup2(in, STDIN_FILENO);
        if (ret == 0 && (list->outfile || list->appendfile))
            dup2(out, STDOUT_FILENO);
        if (ret == 0 && list->next)                             // && !list->outfile && !list->appendfile)
            ft_close(data->fd[1], strerror(errno));
        if (ret == 0 && list->prev)                             // && !list->infile)
            ft_close(data->fd_in, strerror(errno));
        if (ret == 0 && list->next)
            data->fd_in = data->fd[0];
        list = list->next;
    }
    if (ret == 0)
        ret = wait_pid(data->pid, data->k);
    free(data->pid);
    return (ret);
}
