/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingsignals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:59:14 by ohassani          #+#    #+#             */
/*   Updated: 2024/07/01 14:38:49 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printsignalsc(int signal)
{
    if (signal == SIGINT)
    {
        if (my_signal.pipef == 1)
        {
            printf("\n");
            my_signal.pipef = 0;
        }
        else if (my_signal.flag_sig == false)
        {
            printf("\n");
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
            my_signal.ret = 130;
        }
    }
    else if (signal == SIGQUIT)
    {
        printf("Quit (core dumped)\n");
    }
    my_signal.flag_sig = false;
}

void handlersignals()
{

    if (signal(SIGINT, printsignalsc) == SIG_ERR)
    {
        perror("fail my signal");
        exit(1);
    }
     if (my_signal.flag_sig == false) 
     {
       signal(SIGQUIT, SIG_IGN);
    } 
    else 
    {
        if (signal(SIGQUIT, printsignalsc) == SIG_ERR) 
        {
            perror("Failed to set SIGQUIT handler");
            exit(1);
        }
    }
}

