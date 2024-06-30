/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingsignals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:59:14 by ohassani          #+#    #+#             */
/*   Updated: 2024/06/30 16:55:43 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printsignalsc(int signal)
{
    if (signal == SIGINT && my_signal.flag_sig == true && my_signal.pipef != 1)
    {
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        my_signal.ret = 130;
    }
    if (signal == SIGINT && my_signal.pipef == 1)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        my_signal.pipef = 0;
    }
    else
    {
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

