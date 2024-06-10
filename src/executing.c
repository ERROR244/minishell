/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/10 19:11:43 by ksohail-         ###   ########.fr       */
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
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(com[0], 2);
            ft_putstr_fd(": ", 2);
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
        }
        else
            run_builtins(cmd, command, data);
        exit(-1);
    }

    free(path);
    if (data->pid[index] < 0)
        return (-1);
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
				return (1);
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
				return (1);
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
	while (i >= 0)
		waitpid(pid[i--], 0, 0);
	return (status);
}

void    change_underscore(t_env *head, t_command *command)
{
    t_env   *index;
    char    *str;
    int     i;

    i = 0;
    while (command->cmd[i])
        i++;
    str = command->cmd[--i];
    index = findmyindex(head, "_");
    if (!str || *str == '\n' || is_spaces(str) == 0)
        return ;
    if (index)
    {
        free(index->var_name);
        index->var_name = ft_strjoin("_=", str);
    }
    else
    {
        index = env_new(head, ft_strjoin("_=", str));
        head = env_last(head);
        head->next = index;
    }
}

int run_builtins(int c, t_command *command, t_data *data)
{
    t_env *list;
    
    list = data->list_env;
    if(c == 1)
        my_cd(list, command->cmd);
    else if (c == 2)
        mypwd(list);
    else if (c == 3)
        printmyenv(list);
    else if (c == 4)
        export(list, command->cmd);
    else if (c == 5)
        list = unset_env(list, command->cmd, data);
    else if (c == 6)
        exit_myminishell(command->cmd);
    else if (c == 7)
        ft_echo(command->cmd + 1, true, 0);
    return (0);
}

int executing(t_data *data)
{
    t_command   *list;
    int         in;
    int         out;

    list = data->list;
    bool flag = false;
    int builtins = get_command_in_one_char(list->cmd);
    data->pid = malloc(sizeof(int) * (get_command_size(list)));
    data->k = 0;
    if(!list || (list->cmd && list->cmd[0][0] == '\n'))
    {
        free(data->pid);
        return (2);
    }
    else if (builtins != 0)
    {
        in = dup(STDIN_FILENO);
        out = dup(STDOUT_FILENO);
        if(list->infile || list->outfile || list->appendfile)
            ret = hand_the_redirectionin(list, in, out);
        change_underscore(data->list_env, list);
        run_builtins(builtins, list, data);
        if ((ret != 1) && list->infile)
            dup2(in, STDIN_FILENO);
        else
            ft_close(in, strerror(errno));
        if ((ret != 1) && (list->outfile || list->appendfile))
            dup2(out, STDOUT_FILENO);
        else
            ft_close(out, strerror(errno));
        change_underscore(data->list_env, list);
    }
    else
    {
        data->fd_in = STDIN_FILENO;
        if (!list->next)
        {
            change_underscore(data->list_env, list);
            flag = true;
        }
        while (list)
        {
            if (list->next)
            {
                if (pipe(data->fd) == -1)
                    break ;
            }
            in = dup(STDIN_FILENO);
            out = dup(STDOUT_FILENO);


            
            if(list->infile || list->outfile || list->appendfile)
                ret = hand_the_redirectionin(list, in, out);


            if (ret != 1 && list->infile)
                dup2(STDIN_FILENO, in);
            else
                ft_close(in, "in");
            if (ret != 1 && (list->outfile || list->appendfile))
                dup2(STDOUT_FILENO, out);
            else
                ft_close(out, "out");
            
            ret = execute_command(data->list_env, list, data, data->k++);



            if (list->next)
                ft_close(data->fd[1], strerror(errno));
            if (list->prev)
                ft_close(data->fd_in, strerror(errno));

                
            if (list->next)
                data->fd_in = data->fd[0];
            else
                break ;
            list = list->next;
        }
        if (flag == true)
            change_underscore(data->list_env, list);
    }
    if (ret == 0 && data->k != 0)
        ret = wait_pid(data->pid, data->k);
    free(data->pid);
    return (ret);
}
