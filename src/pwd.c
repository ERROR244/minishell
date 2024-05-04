/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:15:57 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 16:15:58 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_pwd(char *str)
{
    char *cur;
    char buff[PATH_MAX];
    cur = getcwd(buff, PATH_MAX);
    if( cur != NULL )
        printf("%s\n", cur);
}