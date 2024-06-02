/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 18:59:09 by ksohail-         ###   ########.fr       */
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
    char **export;

    i = 1;
    if(com[1] == NULL)
        printmyexport();
    while(com[i])
    {
        if(ft_isalpha(com[i][0]) != 1)
            printf("export: '%s' :not a valid identifier\n", com[i]);
        export = ft_split(com[i], '=');
        set_myenv(export[0], export[1]);
        i++;
    }
    // free_array(export);
}
