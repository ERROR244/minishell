/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:29:48 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/05 16:40:05 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ben10(size_t n, unsigned char *ptr1, const unsigned char *ptr2)
{
	while (n > 0)
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (unsigned char *)dest;
	ptr2 = (const unsigned char *)src;
	if (ptr1 == ptr2)
		return (dest);
	else if (ptr1 < ptr2)
		ben10(n, ptr1, ptr2);
	else
	{
		ptr1 += n - 1;
		ptr2 += n - 1;
		while (n > 0)
		{
			*ptr1 = *ptr2;
			ptr1--;
			ptr2--;
			n--;
		}
	}
	return (dest);
}
