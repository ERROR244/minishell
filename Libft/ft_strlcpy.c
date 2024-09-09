/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:03:59 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/17 13:44:31 by ksohail-         ###   ########.fr       */
=======
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:03:59 by ksohail-          #+#    #+#             */
/*   Updated: 2024/06/01 10:26:15 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
<<<<<<< HEAD
=======
	if (!dst || !src)
		return (0);
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && size - 1 > 0)
	{
		dst[i] = src[i];
		size--;
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
