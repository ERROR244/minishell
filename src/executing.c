/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/03 15:50:47 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// executing_command
void execute_command(char **com)
{
    int pid;

    if (com[0][0] == '\0')
    {
        ft_putstr_fd("minishell: command '' not found\n", 2);
        return ;
    }
    char *path = get_my_path(com);
    if(path == NULL)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(com[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        return ;
    }
    // dprintf(2,"path %s\n",path);
    // dprintf(2,"com => %s\n",*com);
    pid = fork();
    // char *cmds[2] = {path,*com};
    if (pid == 0)
    {
        execve(path, com, myenv);
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(com[0], 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        exit(1);
    }
    else if (pid < 0)
    {
        free(path);
        return;
    }
    else
        wait(&pid);
    if (path)
        free(path);
}

void ft_pipe(t_cmds *lst)
{
    int fd[2];
    if(pipe(fd) == -1)
        return;
    
    int pid1 = fork();
    if(pid1 == -1)
        return;

    if(pid1 == 0)
    {
        close(fd[0]); 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); 
        execute_command(&lst->prev->cmd[0]);
        exit(1); 
    }

    int pid2 = fork();
    if(pid2 == -1)
        return;
    else if(pid1 != 0)
    {
        if(pid2 == 0)
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]); 
            execute_command(&lst->next->cmd[0]);
            exit(1); 
        }
    }

    close(fd[0]); 
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0); 
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
		printf("---------------->%d \n", fd[i]);
		i++;
	}
	if (fd)
		free(fd);
}

int *ft_open(t_slist *list, bool infile)
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
			if (infile == true)
				fd[j] = open(list->cmd[i], O_RDONLY);
			else
				fd[j] = open(list->cmd[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			printf("%d--%d\n", fd[j], j);
			
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
			
			j++;
			i++;
		}
		list = list->next;
	}
	printf("%d--%d\n", fd[j], j);
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

void hand_theredirectionin(t_command *lst)
{
    int out = dup(STDOUT_FILENO);
    int in = dup(STDIN_FILENO);
    int *filein  = NULL;
    int *fileout = NULL;
	int last1;
	int last2;
    
    while (lst)
    {
        if(lst->infile != NULL)
        {
            filein = ft_open(lst->infile, true);
			
            if(!filein)
			{
	        	close(in);
				return ;
			}
            else
			{
				last1 = get_last_index(filein);
            	dup2(filein[last1], STDIN_FILENO);
			}

        }
        if(lst->outfile != NULL)
        {
            fileout = ft_open(lst->outfile, false);

            if(!fileout)
			{
        		close(out);
				return ;
			}
            else
			{
				last2 = get_last_index(fileout);
            	dup2(fileout[last2], STDOUT_FILENO);
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
    execute_command(lst->cmd);
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

    list = data->list;
    if(!list->cmd || list->cmd[0] == NULL || list->cmd[0][0] == '\n')
        return ;
    else if(ft_strcmp(list->cmd[0], "cd") == 0)   
        my_cd(list->cmd);
    else if(ft_strcmp(list->cmd[0], "pwd") == 0)
        mypwd();
    else if(ft_strcmp(list->cmd[0], "env") == 0 && list->cmd[1] == NULL)
        printmyenv();
    else if(ft_strcmp(list->cmd[0], "export") == 0)
        export(list->cmd);
    else if(ft_strcmp(list->cmd[0], "unset") == 0)
        unset_env(list->cmd);
    else if(ft_strcmp(list->cmd[0], "exit") == 0)
        exit_myminishell(list->cmd);
    else if(ft_strcmp(list->cmd[0], "echo") == 0)
    {
        if (!list->cmd[1])
            printf("\n");
        else
            ft_echo(list->cmd + 1, true);
    }

    else if(list->infile != NULL || list->outfile != NULL)
    {
        hand_theredirectionin(list);
    }
    else
        execute_command(list->cmd);
}
