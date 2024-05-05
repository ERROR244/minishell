/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:11:30 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/10 16:26:38 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(little);
	if (needle_len == 0)
		return ((char *)big);
	if (*big == '\0' || len < needle_len)
		return (NULL);
	while (*big != '\0' && len >= needle_len)
	{
		if (ft_strncmp(big, little, needle_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
