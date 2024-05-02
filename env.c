#include "minishell.h"

void put_our_env(t_data **data, char *key, char *value)
{
    t_data *newnode = (t_data *)malloc(sizeof(t_data));

    newnode->key = ft_strdup(key);
    newnode->value = ft_strdup(value);
    newnode->next = NULL;
    
    if(*data == NULL)
    {
        *data = newnode;
    }
    else
    {
        t_data *tmp = *data;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newnode;
    }

}
void copy_the_envi(char **env , t_data **data)
{
    char **enviroment = env;

    char **split;
    while(*enviroment != NULL)
    {
        split  = ft_split(*enviroment, '=');
        put_our_env(data, split[0],split[1]);
        enviroment++;
    }
}

void print_environment(t_data *data)
{
    t_data *current = data;
    while(current != NULL)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

