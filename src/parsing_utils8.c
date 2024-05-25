/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:26:19 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/25 16:28:39 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_vars(char *s1)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (s1 && *s1)
	{
		if (*s1 == '$' && ft_isalpha(s1[1]) == 1)
        {
            s1++;
			if (*s1 != '$')
            {
                while (*s1 && ft_isalpha(s1[0]) == 1)
			    {
                    s1++;
                }
			    in_word = 0;
            }
        }
		else if (in_word == 0)
		{
		    count++;
            while (*s1 && (*s1 != '$' || (ft_isalnum(s1[0]) == 1) || !s1[1]))
		    {
				if (s1[0] == '$' && s1[1] == '$')
					s1++;
                s1++;
            }
		    in_word = 1;
		}
        else
    		s1++;
	}
	return (count);
}

int	dollar_is_in(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
			k++;
		i++;
	}
	return (k);
}
