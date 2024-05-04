/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:07:09 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 16:44:50 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void executing(t_data *data)
{
    char *str = data->lst->cmd;
    if (ft_strcmp(str, "pwd") == 0)
        ft_pwd(str);
    if (ft_strcmp(str, "cd") == 0)
        ft_cd(str, &data);
    if (ft_strcmp(str, "env") == 0)
        print_environment(data);
}