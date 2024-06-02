/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 22:57:21 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// executing_command
void execute_command(char **com)
{
    int pid;

    if (com[0][0] == '\0')
    {
        ft_putstr_fd("command '' not found\n", 2);
        return ;
    }
    char *path = get_my_path(com);
    if(path == NULL)
    {
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
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        // perror("command not found:");
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

void hand_theredirectionin(t_command *lst)
{
    int out = dup(STDOUT_FILENO);
    int in = dup(STDIN_FILENO);
    int filein;
    int fileout;
    
    // printf("%s\n", lst->cmd[0]);
    while (lst)
    {
        if(lst->infile != NULL)
        {
            filein = open(lst->infile->cmd[0], O_RDONLY);

            if(filein == -1)
                perror("fail the file\n");
            
            // dup2(STDIN_FILENO, filein);
            dup2(filein, STDIN_FILENO);

        }
        if(lst->outfile != NULL)
        {
            fileout = open(lst->outfile->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);

            if(fileout == -1)
                perror("fail the file\n");
            
            // dup2(STDOUT_FILENO, fileout);
            dup2(fileout, STDOUT_FILENO);
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
    dup2(out, fileout);
    dup2(in, filein);
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
