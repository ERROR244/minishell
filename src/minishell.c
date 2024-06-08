/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/08 17:38:05 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char **myenv = NULL;

char *get_exit_status(int ret)
{
	char	*exit_status;
	char	*tmp;

	tmp = ft_itoa(ret);
	exit_status = ft_strjoin("?=", tmp);
	free(tmp);
	return (exit_status);
}

int main(int ac, char **av, char **env)
{
    t_data data;
	int ret;
	
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
			ret = parsing(&data);
		}
		free(data.line);
		free_array(data.env);
		free(data.list_env->var_name);
		data.list_env->var_name = get_exit_status(ret);
    }
	if (data.env)
		free_array(data.env);
	senv_clear(&data.list_env);
	printf("exit\n");
    return (0);
}
