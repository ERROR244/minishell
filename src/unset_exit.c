/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:13 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/30 16:46:47 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env *remove_node(t_env *head, t_env *node_to_remove)
{
    if (!head || !node_to_remove)
        return (head);

    if (node_to_remove == head)
    {
        head = node_to_remove->next;
        if (head)
            head->prev = NULL;
        free(node_to_remove->var_name);
        free(node_to_remove);
        return (head);
    }

    if (node_to_remove->prev)
        node_to_remove->prev->next = node_to_remove->next;
    if (node_to_remove->next)
        node_to_remove->next->prev = node_to_remove->prev;

    free(node_to_remove->var_name);
    free(node_to_remove);

    return (head);
}

t_env   *unset_env(t_env *list, char **com, t_data *data)
{
    t_env   *index;
    int i;


    i = 0;
    index = NULL;
    while(com[i])
    {
        if (data->path_flag == true && ft_strcmp(com[i], "PATH") == 0)
            data->path_flag = false;
        index  = findmyindex(list, com[i]);
        if(index)
            list = remove_node(list, index);
        i++;
    }
    return (list);
}

int is_numeric(char *str)
{
    while (*str)
    {
        if (ft_isdigit(*str) == 0)
            return (1);
        str++;
    }
    return (0);
}

void exit_myminishell(char **com, int flag)
{
    int i;

    if (flag != 0)
    {
        if(com[1] == NULL)
            exit(0);
        else if (is_numeric(com[1]) != 0)
            exit(2);
        else if (com[1] && com[2])
            ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        else
        {
            i = ft_atoi(com[1]);
            my_signal.ret = i;
            exit(i);
        }
        return ;
    }

    if(com[1] == NULL)
    {
    	printf("exit\n");
        exit(0);
    }
    else if (is_numeric(com[1]) != 0)
    {
        printf("minishell: ");
        printf(com[1], 2);
        printf(": numeric argument required\n");
        exit(2);
    }
    else if (com[1] && com[2])
        printf("minishell: exit: too many arguments\n");
    else
    {
        i = ft_atoi(com[1]);
	    printf("exit\n");
        my_signal.ret = i;
        exit(i);
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

char *get_my_path(t_env *list, char **com, bool flag) 
{
    char **str;
    char *path1;

    if (com[0][0] == '/' || com[0][0] == '.')
        return (ft_strdup(com[0]));
    path1 = findmyvar(list, list, "PATH", flag);
    if (!path1) 
        return (NULL);
    str = ft_split(path1, ':');
    if (!str)
        return (NULL);
    int i = 0;
    char *mypath = (NULL);
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
   free_array(str);
    if (!mypath)
        return (NULL);
    return (mypath);
}
