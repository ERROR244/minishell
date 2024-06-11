/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingsignals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:59:14 by ohassani          #+#    #+#             */
/*   Updated: 2024/06/11 23:25:06 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void printsignalsc(int signal)
{
    if (signal == SIGINT && flag_sig == true)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        ret = 130;
    }
    else
    {
        rl_replace_line("", 0);
        rl_on_new_line();
        printf("\n");
        rl_redisplay();
        ret = 0;
    }
    flag_sig = false;
}
void handlersignals()
{
        
    if( signal(SIGINT, printsignalsc) == SIG_ERR)
    {
        perror("fail my signal");
        exit(1);
    }
     if( signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
        perror("fail my signal");
        exit(1);
    }
}

