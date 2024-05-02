/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/02 17:28:45 by error01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_array(char **array)
{
    char **ptr = array;
    while (*ptr)
	{
        free(*ptr);
        ptr++;
    }
    free(array);
}


void parsing(t_data *data)
{
	char **cmds;
	int i;

	i = 0;
	data->line = ft_strdup(data->line);
	cmds = ft_split(data->line);

	for (int i = 0; cmds[i]; i++)
		printf("%s\n", cmds[i]);
	free_array(cmds);
}

int main(int ac, char **av, char **env)
{
    t_data data;

	if (ac != 1)
		return (1);
	data.env = env;
    while (env != NULL)
    {
		printf("minishell$ ");
		data.line = readline(NULL);
		if (data.line == NULL)
			break;
		parsing(&data);
		// executing();						to do
		free(data.line);
    }
	printf("\n");
	
    return (0);
}