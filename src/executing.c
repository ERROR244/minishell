/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/27 15:58:23 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// copy_env

int lenofmyenv(char **env)
{
    int i = 0;
    int mylen = 0;

    while(env[i])
    {
        i++;
        mylen++;
    }
    return(mylen);

}

void exiterror(void)
{
    free_array(myenv);
    write(1, "\n", 1);
    exit(1);
}

void  copieenv(char **env)
{
    int len = lenofmyenv(env);
    myenv = (char **)malloc((len + 1)*sizeof(char *));
    
    if(!myenv)
        exiterror();
    int i = 0;
    while(env[i])
    {
        myenv[i] = ft_strdup(env[i]);
        if(!myenv[i])
        {
            exiterror();
        }
        i++;
    }
    myenv[i] = NULL;
}

//  cd

int findmyindex(char *va)
{
    int i = 0;
    char *tmp;
    tmp = ft_strjoin(va, "=");
    if (tmp && tmp[0] == '=' && tmp[1] == '\0')
    {
        free(tmp);
        tmp = NULL;
    }
    int len = ft_strlen(tmp);
        while(myenv[i])
        {
            if(ft_strncmp(myenv[i], tmp, len) == 0)
            {
                    free(tmp);
                    return(i);
            }
            i++;
        }
        free(tmp);
        return(0);
}

void set_myenv(char *key, char *value)
{
    int myi = findmyindex(key);
    char *tmp = ft_strjoin("=", value);
    int i = 0;

    while (myenv[i])
        i++;
    if(myi != 0)
    {
        free(myenv[myi]);
        if(value)
            myenv[myi] = ft_strjoin(key, tmp);
        else
            myenv[myi] = ft_strjoin(key, "=");
    }
    else
    {
        myenv = (char **)realloc(myenv, (sizeof(char *) * i) + 8);
        if(value)
            myenv[i - 1] = ft_strjoin(key, tmp);
        else
            myenv[i - 1] = ft_strjoin(key, "= "" ");
        myenv[i] = NULL;
    }
    free(tmp);
}

void change_mydir(char *path)
{
    char *cur;
    char buffer[PATH_MAX];
    cur = getcwd(buffer, PATH_MAX);

    if(chdir(path) != 0)
    {
        perror("cd");
    }
	set_myenv("OLDPWD", cur);
    set_myenv("PWD", path);
}

char *findmyvar(char *va)
{
    int i = 0;
    char *tmp;
    tmp = va;
        while(myenv[i])
        {
            char **vale = ft_split(myenv[i], '=');
            if(ft_strcmp(vale[0], tmp) == 0)
            {
                    return(ft_strchr(myenv[i], '=')) + 1;
            }
            i++;
        }
        free(tmp);
        return(0);
}

int morethan2arg(char **com)
{
    int i = 0;
    int counter = 0;
    while(com[i])
    {
        i++;
        counter++;
    }
    return(counter);
}

void my_cd(char **com)
{
    int counter = morethan2arg(com);
    printf("%d \n", counter);
    if(counter > 2)
    {
        ft_putstr_fd("cd: too many arguments", 1);
        exit(1);
    }
    char *myhome = findmyvar("HOME");
    if(com[1] == NULL || com[1][0] == '~')
        change_mydir(myhome);
    else 
        change_mydir(com[1]);
}


// pwd

void mypwd(void)
{
    char *cur;
    char buffer[PATH_MAX];
    cur = getcwd(buffer, PATH_MAX);
    printf("%s\n", cur);
}

// print_env

void ft_putendle(char *str, int fd)
{
    if(!str)
		return;
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}

void printmyenv()
{
    int		i;

	i = 0;

	while (myenv[i])
    {
		ft_putendle(myenv[i], 1);
        i++;
    }
}


void executing(t_data *data)
{
    // char **tmp = data->cmds;
    
    // for (int i = 0; tmp[i]; i++)
    //     printf(":%s:\n", tmp[i]);
    // t_cmds *lst = data->lst;
    // while (lst)
    // {
    //     for (int i = 0; lst->cmd[i]; i++)
    //         printf(":%s:\n", lst->cmd[i]);
    //     lst = lst->next;
    // }
    
    if(data->lst->cmd[0] == NULL)
        return ;
    else if(ft_strcmp(data->lst->cmd[0], "cd") == 0)   
        my_cd(data->lst->cmd);
    else if(ft_strcmp(data->lst->cmd[0], "pwd") == 0)
        mypwd();
    else if(ft_strcmp(data->cmds[0], "env") == 0 && data->cmds[1] == NULL)
        printmyenv();
    // else if(ft_strcmp(data->cmds[0], "echo") == 0)
    // {
    //     if(data->cmds[1] != NULL && ft_strcmp(data->cmds[1], "-n") == 0)
    //         ft_echo_n(data->cmds);
    //     else
    //         ft_echo(data->cmds);
    // }
    // else if(ft_strcmp(data->cmds[0], "export") == 0)
    //     export(data->cmds);
    // else if(ft_strcmp(data->cmds[0], "exit") == 0)
    //     exit_myminishell(data->cmds);
    // else if(ft_strcmp(data->cmds[0], "unset") == 0)
    //     unset_env(data->cmds);
    // else
    // {
        // printf("i enter here\n");
        // printf("%s\n", com[0]);
    // }
}
