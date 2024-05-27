/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:03:16 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/27 17:44:23 by ksohail-         ###   ########.fr       */
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

// export

void ft_putendexp(char *str, int fd)
{
    char	*tmp;

    if(!str)
            return ;
	tmp = ft_strjoin(str, "\n");
    ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

// void ft_putendexp(char *str, int fd)
// {
//     if(!str)
//         return ;
//     ft_putstr_fd("declare -x ", 1);
// 	ft_putstr_fd(str, fd);
// 	ft_putstr_fd("\n", fd);
// }

void swap(char **s1, char **s2)
{
     char *tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

int comparestring(char *s1, char *s2)
{
    return ft_strcmp(s1, s2);
}

void sortexport(char **arr, int n)
{
    int i = 0;
    while(i < n - 1)
    {
        int j = 0;
        while(j < n  - i - 1)
        {
            if(comparestring(arr[j], arr[j + 1]) > 0)
                swap(&arr[j], &arr[j + 1]);
            j++;
        }
        i++;
    }
}

void printmyexport()
{
    int		i;

	i = 0;

    while(myenv[i])
        i++;

    sortexport(myenv, i);

    int j = 0;
	while (myenv[j])
    {
		ft_putendexp(myenv[j], 1);
        j++;
    }
}

void export(char **com)
{
    int i;
    
    i = 1;
    if(com[1] == NULL)
        printmyexport();
    while(com[i])
    {
        if(ft_isalpha(com[i][0]) != 1)
            printf("export: '%s' :not a valid identifier\n", com[i]);
        char **export = ft_split(com[i], '=');
        set_myenv(export[0], export[1]);
        i++;
    }
}

// unset

void unset_env(char **com)
{
    if(com[1] == NULL)
        return ;
    int i = 1;
    int j;
    while(com[i])
    {
        j  = findmyindex(com[i]);
        if(j > 0)
        {
            free(myenv[j]);
            myenv[j] = NULL;
        }
        i++;
    }
}

//  exit

void exit_myminishell(char **com)
{
    int a;
    if(com[1] == NULL)
        exit(0);
    if(ft_isdigit(com[1][0]) == 1)
    {
        a = com[1][0]; 
        if(a == '1')
            exit(1);
        else if(a == '0')
            exit(0);
    }
    else
    {
        ft_putstr_fd(com[1], 1);
        printf("%s",": numeric argument required\n");
        exit(1);
    }
}

// executing_command

static char	*join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*concatenated;
	size_t	j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	concatenated = (char *)malloc((len1 + len2) * sizeof(char) + 1);
	if (concatenated == NULL)
		return (NULL);
	while (len1 > i)
	{
		concatenated[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		concatenated[i++] = s2[j++];
	concatenated[len1 + len2] = '\0';
	return (concatenated);
}

char *get_my_path(char **com) 
{
    char *path1 = findmyvar("PATH");
    if (!path1) 
        return NULL;

    char **str = ft_split(path1, ':');
    if (!str)
        return NULL;

    int i = 0;
    char *mypath = NULL;
    while (str[i]) 
    {
        char *joiner = join(str[i], "/");

        char *command_path = ft_strjoin(joiner, com[0]);
        free(joiner);

        if (access(command_path, X_OK) == 0) 
        {
            mypath = command_path; 
            break;
        }

        free(command_path);
        i++;
    }

    i = 0;
   free_array(str);

    if (!mypath)
        return NULL;

    return mypath;
}

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
    // if (path)
    //     free(path);

}

void executing(t_data *data)
{
    if(data->lst->cmd[0] == NULL)
        return ;
    else if(ft_strcmp(data->lst->cmd[0], "cd") == 0)   
        my_cd(data->lst->cmd);
    else if(ft_strcmp(data->lst->cmd[0], "pwd") == 0)
        mypwd();
    else if(ft_strcmp(data->lst->cmd[0], "env") == 0 && data->lst->cmd[1] == NULL)
        printmyenv();
    else if(ft_strcmp(data->lst->cmd[0], "export") == 0)
        export(data->lst->cmd);
    else if(ft_strcmp(data->lst->cmd[0], "unset") == 0)
        unset_env(data->lst->cmd);
    else if(ft_strcmp(data->lst->cmd[0], "exit") == 0)
        exit_myminishell(data->lst->cmd);
    // else if(ft_strcmp(data->lst->cmd[0], "echo") == 0)
    // {
    //     if(data->lst->cmd[1] != NULL && ft_strcmp(data->lst->cmd[1], "-n") == 0)
    //         ft_echo_n(data->lst->cmd);
    //     else
    //         ft_echo(data->lst->cmd);
    // }
    else
        execute_command(data->lst->cmd);
}
