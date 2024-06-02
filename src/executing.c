/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 19:09:26 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// executing_command

void execute_command(char **com)
{
    int pid;

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

void executing(t_data *data)
{

    t_command *list;

    list = data->list;
    if(list->cmd[0] == NULL)
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
        if(list->cmd[1] != NULL && ft_strcmp(list->cmd[1], "-n") == 0)
            ft_echo(list->cmd + 1, false);
        else
            ft_echo(list->cmd + 1, true);
    }
    else
        execute_command(list->cmd);
}
