/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/07 10:09:31 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_signal	g_signal;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (1);
	(void)av;
	g_signal.ret = 0;
	g_signal.flag_heredoc = false;
	data.path_flag = false;
	g_signal.ff = 0;
	if (!env[0])
		data.path_flag = true;
	data.list_env = copieenv(env);
	while (1)
	{
		signal_handler();
		data.env = linked_list_to_array(data.list_env);
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
		g_signal.ff = 0;
	}
	if (data.env)
		free_array(data.env);
	senv_clear(&data.list_env);
	ft_putstr_fd("exit\n", 2);
	return (0);
}
