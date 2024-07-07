/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingsignals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:59:14 by ohassani          #+#    #+#             */
/*   Updated: 2024/07/07 08:58:16 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printsignalsc(int signal)
{
    if (signal == SIGINT)
    {
        {
            printf("\n");
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
            my_signal.ret = 130;
        }
    }
}
void signal_hand2(int s)
{
    (void)s;
    signal(SIGINT,SIG_DFL);
    write(1, "\n", 1);
}
// void signal_hand2(int signal)
// {
//     void signal_hand2(int signal);
// }

 void    ft_handle_sigint(int sig)
{
    if(my_signal.ff == 1)
        return;
    (void)sig;
    printf("\n");
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
    my_signal.ret = 130;

}

void    signal_handler(void)
{ 
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ft_handle_sigint);
    signal(SIGTSTP, SIG_IGN);
}