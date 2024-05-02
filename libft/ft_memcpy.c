/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:30:18 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/06 21:30:19 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dtr;
	const unsigned char	*str;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	dtr = (unsigned char *)dst;
	str = (const unsigned char *)src;
	while (n > 0)
	{
		dtr[i] = str[i];
		i++;
		n--;
	}
	return (dtr);
}

// #include <string.h>

// int	main(void)
// {
// 	memcpy("NULL", "NULL", 3);
// 	// printf("%s\n%s\n",p, q);
// }