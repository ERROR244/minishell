/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:01:41 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/16 11:24:48 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	k;
	int		i;

	k = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == k)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
