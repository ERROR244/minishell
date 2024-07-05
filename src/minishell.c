/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/04 19:42:18 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_signal my_signal;

int main(int ac, char **av, char **env)
{
    t_data	data;
	
	if (ac != 1)
		return (1);
	(void)av;
	my_signal.ret = 0;
	my_signal.flag_heredoc = false;
	data.path_flag = false;
	my_signal.ff = 0;
	if (!env[0])
		data.path_flag = true;
	data.list_env = copieenv(env);
    while (1)
    {
		signal_handler();
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
		my_signal.ff = 0;
    }

	if (data.env)
		free_array(data.env);
	senv_clear(&data.list_env);
	ft_putstr_fd("exit\n", 2);
    return (0);
}
