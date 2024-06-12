/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingsignals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:59:14 by ohassani          #+#    #+#             */
/*   Updated: 2024/06/12 01:05:28 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printsignalsc(int signal)
{
    if (signal == SIGINT && my_signal.flag_sig == true)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        my_signal.ret = 130;
    }
    else
    {
        // if (my_signal.flag_heredoc == true)
        //     my_signal.flag_heredoc = false;
        rl_replace_line("", 0);
        rl_on_new_line();
        printf("\n");
        rl_redisplay();
        my_signal.ret = 130;
    }
    my_signal.flag_sig = false;
}

// void signalfunc(int pid)
// {
//     if(pid == SIGINT)
//     {
//         printf("HERE\n");
//         my_signal.flag_heredoc = false;
//     }
// }
void handlersignals()
{
        
    // if (my_signal.flag_heredoc == true)
    //     signal(SIGINT, signalfunc);
    if (signal(SIGINT, printsignalsc) == SIG_ERR)
    {
        perror("fail my signal");
        exit(1);
    }
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
        perror("fail my signal");
        exit(1);
    }

}

