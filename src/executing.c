/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/06 17:42:19 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// executing_command
void execute_command(t_env *list, t_command *command, t_data *data)
{
    char **com = command->cmd;
    int pid;

    if (!com)
        return ;
    if (com[0][0] == '\0')
    {
        ft_putstr_fd("minishell: command '' not found\n", 2);
        return ;
    }
    char *path = get_my_path(list, com);
    if(path == NULL)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(com[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        if (command->prev && !command->infile && data->tmp != -1)
        {
            // ft_putstr_fd("IN", 2);
            // printf(" --> %d \n", data->tmp);
            // ft_putstr_fd(command->cmd[0], 2);
            // ft_putstr_fd("\n", 2);
            // ft_putstr_fd(command->cmd[1], 2);
            // ft_putstr_fd("\n", 2);
            dup2(data->tmp, STDIN_FILENO);
            close(data->tmp);
        }
    	if (command->next && !command->outfile && !command->appendfile)
        {
            close(data->fd[0]);
            // ft_putstr_fd("OUT", 2);
            // printf(" --> %d \n", data->tmp);
            // ft_putstr_fd(command->cmd[0], 2);
            // ft_putstr_fd("\n", 2);
            // ft_putstr_fd(command->cmd[1], 2);
            // ft_putstr_fd("\n", 2);
            dup2(data->fd[1], STDOUT_FILENO);
            close(data->fd[1]);
        }
        execve(path, com, data->env);
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(com[0], 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        exit(1);
    }
    else if (pid < 0)
    {
        // close(data->fd[0]);
        close(data->tmp);
        close(data->fd[1]);
        free(path);
        return;
    }
    else
        wait(&pid);
    if (path)
        free(path);
}

// void ft_pipe(t_env *list, t_cmds *lst, t_data *data)
// {
//     int fd[2];
//     if(pipe(fd) == -1)
//         return;
    
//     int pid1 = fork();
//     if(pid1 == -1)
//         return;

//     if(pid1 == 0)
//     {
//         close(fd[0]); 
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]); 
//         execute_command(list, &lst->prev->cmd[0], data);
//         exit(1); 
//     }

//     int pid2 = fork();
//     if(pid2 == -1)
//         return;
//     else if(pid1 != 0)
//     {
//         if(pid2 == 0)if (token == Infile)
            	//     dup2(fd[j], STDIN_FILENO);
    			// else if (token == OutFile || token == AppendFile)
            	//     dup2(fd[j], STDOUT_FILENO);
//         {
//             close(fd[1]);
//             dup2(fd[0], STDIN_FILENO);
//             close(fd[0]); 
//             execute_command(list, &lst->next->cmd[0], data);
//             exit(1); 
//         }
//     }

//     close(fd[0]); 
//     close(fd[1]);
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0); 
// }

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
	// printf("%d\n", size);
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

void hand_the_redirectionin(t_env *list, t_command *lst, t_data *data)
{
    int out = dup(STDOUT_FILENO);
    int in = dup(STDIN_FILENO);
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
    execute_command(list, lst, data);
    dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);
    ft_close(filein);
    ft_close(fileout);
	close(out);
	close(in);
}


void executing(t_data *data)
{
    t_command *list;

    data->tmp = -1;
    list = data->list;
    while (list)
    {
        if (list->next)
        {
            if (pipe(data->fd) == -1)
                break ;
            printf("%d \n", data->tmp);
            data->tmp = data->fd[0];
            printf("%d \n", data->tmp);
        }
        if(!list || (list->cmd && list->cmd[0][0] == '\n'))
            return ;
        else if(list->infile || list->outfile || list->appendfile)
            hand_the_redirectionin(data->list_env, list, data);
        else if(list->cmd && ft_strcmp(list->cmd[0], "cd") == 0)   
            my_cd(data->list_env, list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "pwd") == 0)
            mypwd(data->list_env);
        else if(list->cmd && ft_strcmp(list->cmd[0], "env") == 0 && list->cmd[1] == NULL)
            printmyenv(data->list_env);
        else if(list->cmd && ft_strcmp(list->cmd[0], "export") == 0)
            export(data->list_env, list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "unset") == 0)
            data->list_env = unset_env(data->list_env, list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "exit") == 0)
            exit_myminishell(list->cmd);
        else if(list->cmd && ft_strcmp(list->cmd[0], "echo") == 0)
        {
            if (!list->cmd[1])
                printf("\n");
            else
                ft_echo(list->cmd + 1, true);
        }
        else
            execute_command(data->list_env, list, data);
        // close(data->tmp);
        close(data->fd[1]);
        list = list->next;
    }
}
