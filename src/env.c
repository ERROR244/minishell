/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:37:53 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/02 21:18:35 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int lenofmyenv(char **env)
{
    int i = 0;
    int mylen = 0;

    while(env[i])
    {
        i++;
        mylen++;
    }
    return(mylen);

}

void exiterror(void)
{
    free_array(myenv);
    write(1, "\n", 1);
    return ;
}

void  copieenv(char **env)
{
    int len = lenofmyenv(env);
    myenv = (char **)malloc((len + 1)*sizeof(char *));
    
    if(!myenv)
        exiterror();
    int i = 0;
    while(env[i])
    {
        myenv[i] = ft_strdup(env[i]);
        if(!myenv[i])
        {
            exiterror();
        }
        i++;
    }
    myenv[i] = NULL;
}

void ft_putendle(char *str, int fd)
{
    if(!str)
		return;
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}

void printmyenv()
{
    int		i;

	i = 0;

	while (myenv[i])
    {
		ft_putendle(myenv[i], 1);
        i++;
    }
}
