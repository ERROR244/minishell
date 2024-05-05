/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/05 05:16:37 by ksohail-         ###   ########.fr       */
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
		add_history(data.line);
		parsing(&data);
		free(data.line);
    }
	printf("\n");
    return (0);
}
