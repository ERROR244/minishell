/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/11 11:13:46 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ret = 0;

int main(int ac, char **av, char **env)
{
    t_data	data;
	
	if (ac != 1)
		return (1);
	(void)av;
	data.path_flag = false;
	if (!env[0])
		data.path_flag = true;
	data.list_env = copieenv(env);
    while (1)
    {
		data.env = linked_list_to_array(data.list_env);;
		data.line = readline("minishell$ ");
		if (!data.line)
			break ;
		else if (check_quotation(data.line) != -1)
		{
			add_history(data.line);
			parsing(&data);
		}
		free(data.line);
		free_array(data.env);
    }

	if (data.env)
		free_array(data.env);
	senv_clear(&data.list_env);
	ft_putstr_fd("exit\n", 2);
    return (0);
}
