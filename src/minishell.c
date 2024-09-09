/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/05 05:16:37 by ksohail-         ###   ########.fr       */
=======
/*   Updated: 2024/07/13 11:50:28 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD
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
=======
t_signal	g_signal;

int	data_init(char **av, t_data *data, char **env)
{
	(void)av;
	g_signal.ret = 0;
	data->path_flag = false;
	g_signal.ff = 0;
	if (!env[0])
		data->path_flag = true;
	data->list_env = copieenv(env);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1 || data_init(av, &data, env) == 0)
		return (1);
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
			parsing(&data, NULL, NULL, -1);
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
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
}
