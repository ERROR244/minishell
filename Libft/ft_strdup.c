/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:47:38 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/09 08:26:40 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;
	int		k;
	int		len;

	len = ft_strlen(s);
	i = 0;
	k = 0;
	ptr = (char *)ft_malloc((len + 1) * sizeof(char), g_signal.node);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[k];
		i++;
		k++;
	}
	ptr[i] = '\0';
	return (ptr);
}
