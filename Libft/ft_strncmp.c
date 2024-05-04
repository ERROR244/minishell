/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:42:46 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/04 16:46:51 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		if (*s1 == '\0' && *s2 == '\0')
			break ;
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	if (s1[i] == '+' || s1[i] == '-' || s1[i] == '0')
		i++;
	while ((s2[i] != '\0' && s1[i] != '\0'))
	{
		if (s1[i] != s2[i])
			d = s1[i] - s2[i];
		i++;
	}
	return (d);
}
