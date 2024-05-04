/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 16:45:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **env)
{
    t_data data;

	if (ac != 1)
		return (1);
	(void)av;
    copy_the_envi(env, &data.env);
    while (env != NULL)
    {
		data.line = readline("minishell$ ");
		if (data.line == NULL)
			break;
		parsing(&data);
		executing(&data);						// to do
		free(data.line);
		lstclear(&data.lst);
    }
	printf("\n");
    return (0);
}
