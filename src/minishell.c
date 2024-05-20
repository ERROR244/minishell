/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/20 13:29:14 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_quotation(char *str)
{
	char *ptr;
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i])
			{
				if (str[i] == 39)
					break ;
				i++;
			}
		}
		if (str[i] == '\0')
		{
        	errormsg(" 'newline'");
			free(str);
			return (NULL);
		}
		i++;
	}
	// free(str);
	// return (ptr);
	(void)ptr;
	return (str);
}

int main(int ac, char **av, char **env)
{
    t_data data;

	if (ac != 1)
		return (1);
	(void)av;
	data.env = env;
    while (1)
    {
		data.line = readline("minishell$ ");
		data.line = check_quotation(data.line);
		if (data.line == NULL)
			break;
		add_history(data.line);
		printf("%s \n", data.line);
		// parsing(&data);
		free(data.line);
    }
	printf("\n");
    return (0);
}
