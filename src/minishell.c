/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 17:53:59 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **env)
{
    t_data data;

	if (ac != 1)
		return (1);
	(void)av;
	(void)env;
    while (1)
    {
		data.line = readline("minishell$ ");
		if (data.line == NULL)
			break;
		parsing(&data);
		// executing();						to do
		free(data.line);
    }
	printf("\n");
	
    return (0);
}
