/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/01 14:02:19 by error01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **findpaths(t_data *data)
{
	
}

char *findpath(t_data *data)
{
	char **paths;

	paths = findpaths(data);
	
}

void parsing(t_data *data)
{
	int i = 0;
	printf("%s \n", data->line);
	while (data->line[i])
	{
		
	}
}

int main(int ac, char **av, char **env)
{
    t_data data;

	if (ac != 1)
		return (1);
	data.env = env;
    while (env != NULL)
    {
		printf("minishell> ");
		data.line = readline(NULL);
		if (data.line == NULL)
			break;
		parsing(&data);
		// executing(); to do
		free(data.line);
    }
	printf("\n");
	
    return (0);
}