#include "minishell.h"

t_data *find_node(t_data *data, char *key)
{
    t_data *current = data;
    while(current != NULL)
    {
        if(ft_strcmp(current->key, key) == 0)
            return(current);
        current = current->next;
    }
    return(NULL);
}
void add_node(t_data **head, char  *key, char *value) {
    t_data *new_node = (t_data *)malloc(sizeof(t_data));
    if (new_node == NULL) {
        ft_putstr_fd("Error\n", 2);
        exit(1);
    }
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        t_data *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void updatethepwd(t_data **data, char *path, char *oldpath)
{
    t_data *current = *data;
    while(current != NULL)
    {
        if(strcmp(current->key, "PWD") == 0)
            current->value = ft_strdup(path);
        if(strcmp(current->key, "OLDPWD") == 0)
            current->value = ft_strdup(oldpath);
        break;  
        current = current->next;
    }
}
void ft_cd(char *str, t_data **data)
{
    t_data *current = *data;
    // char cur[PATH_MAX];
    // char *dir;
    // dir = NULL;
    // while(current != NULL)
    // {
    //     if(ft_strcmp(current->key, "HOME") == 0)
    //     {
    //         dir = current->value;
    //         break;
    //     }
    //     current= current->next;
    // }
    //     char *path = str + 3;
    //     char *oldpath = getcwd(cur, sizeof(cur));
    // if(ft_strcmp(str , "cd") == 0)
    //     chdir(dir);
    // else 
    //     chdir(path);
    // t_data *oldpath1 = find_node((*data), "OLDPWD");
    // if(oldpath1 == NULL)
    //     add_node(data, "OLDPWD", oldpath);
    // else
    //     updatethepwd(data, path, oldpath);
    char **split = ft_split(str, ' ');

    if (split[1] == NULL)
    {
        chdir(current->value);
    }
    else
    {

    }
}