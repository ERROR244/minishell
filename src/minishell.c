/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/20 16:09:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotation(char *str)
{
	char c;
	int i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			c = str[i];
			while (str[++i])
			{
				if (str[i] == c)
					break ;
			}
		}
		if (str[i] == '\0')
		{
        	errormsg(" 'newline'");
			free(str);
			return (-1);
		}
	}
	return (0);
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
		if (check_quotation(data.line) == -1 || data.line == NULL)
			break;
		add_history(data.line);
		parsing(&data);
		free(data.line);
    }
	printf("\n");
    return (0);
}
