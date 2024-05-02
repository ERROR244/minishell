/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:30:28 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/10 20:59:58 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(const void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*s;

	i = 0;
	ptr = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		while (n > 0)
		{
			ptr[n - 1] = s[n - 1];
			n--;
		}
	}
	else
	{
		ft_memcpy(ptr, s, n);
	}
	return (ptr);
}
// #include <string.h>
// #include<stdio.h>
// int	main(void)
// {
// 	char	*d = "sert9wd";
// 	char	*s = "sert9wd";

// 	printf("%s", ft_memmove(d, s, 4));
// }
