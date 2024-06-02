/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 22:09:26 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **myenv = NULL;

int main(int ac, char **av, char **env)
{
    t_data data;

	if (ac != 1)
		return (1);
	
	if (!env)
		return (1);
	copieenv(env);
	(void)av;
	data.env = env;
    while (1)
    {
		data.line = readline("minishell$ ");
		if (!data.line)
			break ;
		else if (check_quotation(data.line) != -1)
		{
			add_history(data.line);
			parsing(&data);
		}
		free(data.line);
    }
	// printf("exit\n");
    return (0);
}
