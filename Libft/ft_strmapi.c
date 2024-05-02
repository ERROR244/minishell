/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:49:51 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/10 16:17:56 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (*s == '\0')
		return (ft_strdup(""));
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	len--;
	while (len >= 0)
	{
		ptr[len] = f(len, s[len]);
		len--;
	}
	return (ptr);
}
