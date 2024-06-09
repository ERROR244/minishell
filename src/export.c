/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/09 13:22:52 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int count_nodes(t_env *list)
{
    int count;
    t_env *current;
    
    count = 0;
    current = list;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return (count);
}

char **sortexport(char **arr, int n)
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
    return (arr);
}

char **linked_list_to_array(t_env *list)
{
    char    **array;
    t_env   *current;
    int     count;
    int i;

    i = 0; 
    count = count_nodes(list);
    array = (char **)malloc((count + 1) * sizeof(char *));
    if (array == NULL)
        exit(EXIT_FAILURE);
    current = list;
    while (i < count)
    {
        array[i] = ft_strdup(current->var_name);
        if (array[i] == NULL)
        {
            perror("strdup");
            free_array(array);
            return (NULL);
        }
        current = current->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}


void printmyexport(t_env *list)
{
    int		i;
    char    **ptr;

	i = 0;

    ptr = linked_list_to_array(list);
    while (ptr[i])
        i++;
    sortexport(ptr, i);
    i = 0;
	while (ptr[i])
    {
        printf("%s", "declare -x ");
        printf("%s\n", ptr[i]);
        i++;
    }
    free_array(ptr);
}

void export(t_env *list, char **com)
{
    char **export;
    char c;
    char *str;
    bool    export_flag;
    size_t size;
    int i;
    int j;

    i = 1;
    c = '-';
    if(com[1] == NULL)
    {
        printmyexport(list);
        return ;
    }
    else
    {
        while(com[i])
        {
            export_flag = false;
            if(ft_isalpha(com[i][0]) != 1)
                printf("export: '%s' :not a valid identifier\n", com[i]);
            else
            {
                if (com[i][ft_strlen(com[i]) - 1] == '=')
                    export_flag = true;
                export = ft_split(com[i], '=');
                size = ft_strlen(export[0]);
                if (export[0][size - 1] == '+')
                {
                    c = '+';
                    str = malloc(sizeof(char) * size);
                    j = 0;
                    while (export[0][j] != '+')
                    {
                        str[j] = export[0][j];
                        j++;
                    }
                    str[j] = '\0';
                    free(export[0]);
                    export[0] = str;
                }
                set_myenv(list, export[0], export[1], c, export_flag);
                free_array(export);
            }
            i++;
        }
    }
}
