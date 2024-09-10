/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingsignals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:59:14 by ohassani          #+#    #+#             */
/*   Updated: 2024/07/07 10:11:47 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_signals_c(int signal)
{
	if (signal == SIGINT)
	{
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_signal.ret = 130;
		}
	}
}

void	signal_hand2(int s)
{
	(void)s;
	signal(SIGINT, SIG_DFL);
	write(1, "\n", 1);
}

void	ft_handle_sigint(int sig)
{
	if (g_signal.ff == 1)
		return ;
	(void)sig;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_signal.ret = 130;
}

void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGTSTP, SIG_IGN);
}
