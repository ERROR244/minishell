/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/09 19:04:43 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// executing_command

int    get_command_in_one_char(char **str)
{
    int c;

    c = 0;
    if(ft_strcmp(str[0], "cd") == 0)
        c = 1;
    else if(ft_strcmp(str[0], "pwd") == 0)
        c = 2;
    else if(ft_strcmp(str[0], "env") == 0 && str[1] == NULL)
        c = 3;
    else if(ft_strcmp(str[0], "export") == 0)
        c = 4;
    else if(ft_strcmp(str[0], "unset") == 0)
        c = 5;
    else if(ft_strcmp(str[0], "exit") == 0)
        c = 6;
    else if(ft_strcmp(str[0], "echo") == 0)
        c = 7;
    return (c);
}

int execute_command(t_env *list, t_command *command, t_data *data, int index)
{
    char    *path;
    int     cmd;

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
    cmd = get_command_in_one_char(com);
    path = get_my_path(list, com, data->path_flag);
    if(path == NULL && cmd == 0)
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
        if(cmd == 0)
        {
            execve(path, com, data->env);
            ret = -1;
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(com[0], 2);
            ft_putstr_fd(": ", 2);
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
        }
        if(cmd == 1)   
            my_cd(data->list_env, com);
        else if(cmd == 2)
            mypwd(data->list_env);
        else if(cmd == 3)
            printmyenv(data->list_env);
        else if(cmd == 4)
            export(data->list_env, com);
        else if(cmd == 5)
            data->list_env = unset_env(data->list_env, com, data);
        else if(cmd == 6)
            exit_myminishell(com);
        else if(cmd == 7)
            ft_echo(com + 1, true, 0);

        commands_clear(&command);
        free(data->line);
        if (data->env)
            free_array(data->env);
        senv_clear(&data->list_env);
        ft_clear(data);
        exit(ret);
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

void	ft_ft_close(int *fd)
{
	int i = 0;

	while (fd && fd[i] != -11)
	{
		if (fd[i] == -1)
			break;
		ft_close(fd[i], strerror(errno));
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
				ft_ft_close(fd);
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

int hand_the_redirectionin(t_command *lst, int in, int out)
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
	        	ft_close(in, strerror(errno));
				return (0);
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
        		ft_close(out, strerror(errno));
				return (0);
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
    ft_ft_close(filein);
    ft_ft_close(fileout);
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

    if (cmd_num == 0)
            return (0);
	i = cmd_num;
	status = 0;
	waitpid(pid[--i], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (i > 0)
		waitpid(pid[i--], 0, 0);
	return (status);
}


int executing(t_data *data)
{
    t_command   *list;
    int         out = dup(STDOUT_FILENO);
    int         in = dup(STDIN_FILENO);
    bool        flag = false;

    list = data->list;
    data->pid = malloc(sizeof(int) * (get_command_size(list)));
    data->k = 0;
    data->fd_in = STDIN_FILENO;
    if (list && !list->next)
    {
        flag = true;
        if(list->infile || list->outfile || list->appendfile)
            ret = hand_the_redirectionin(list, in, out);
        if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "cd") == 0)
            my_cd(data->list_env, list->cmd);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "pwd") == 0)
            mypwd(data->list_env);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "env") == 0 && list->cmd[1] == NULL)
            printmyenv(data->list_env);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "export") == 0)
            export(data->list_env, list->cmd);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "unset") == 0)
            data->list_env = unset_env(data->list_env, list->cmd, data);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "exit") == 0)
            exit_myminishell(list->cmd);
        else if(ret == 0 && list->cmd && ft_strcmp(list->cmd[0], "echo") == 0)
                ft_echo(list->cmd + 1, true, 0);
        else if (ret == 0)
            ret = execute_command(data->list_env, list, data, data->k++);
    }
    while (list && flag == false)
    {
        if(!list || (list->cmd && list->cmd[0][0] == '\n'))
        {
            free(data->pid);
            return (2);
        }
        if (list->next)
        {
            if (pipe(data->fd) == -1)
                break ;
        }
        if(list->infile || list->outfile || list->appendfile)
            ret = hand_the_redirectionin(list, in, out);
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
    if (ret == 0 && data->k != 0)
        ret = wait_pid(data->pid, data->k);
    free(data->pid);
    return (ret);
}
