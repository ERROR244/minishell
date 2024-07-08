/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:11:49 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/08 18:37:26 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_2d_size(char **vars, char **lines)
{
    int i;
    int size;
	i = 0;
    size = 0;
	while (vars[i])
		size += ft_strlen(vars[i++]);
	i = 0;
	while (lines[i])
		size += ft_strlen(lines[i++]);
    return (size);
}
