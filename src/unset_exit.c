/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:13 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 19:10:29 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void exit_myminishell(char **com)
{
    int a;
    if(com[1] == NULL)
    {
        printf("exit\n");        
        exit(0);
    }
    if(ft_isdigit(com[1][0]) == 1)
    {
        a = com[1][0]; 
        if(a == '1')
        {
            printf("exit\n");
            exit(1);
        }
        else if(a == '0')
        {
            printf("exit\n");
            exit(0);
        }
    }
    else
    {
        ft_putstr_fd(com[1], 1);
        printf("%s",": numeric argument required\n");
        exit(1);
    }
}

char	*join(char const *s1, char const *s2)
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
    char **str;
    char *path1;
    
    path1 = findmyvar("PATH");
    if (!path1) 
        return NULL;

    str = ft_split(path1, ':');
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

    return (mypath);
}
