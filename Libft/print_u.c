/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:20:34 by ksohail-          #+#    #+#             */
/*   Updated: 2024/01/31 21:25:53 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill(char *ptr, unsigned int n, int x)
{
	if (x >= 0)
	{
		ptr[x] = (n % 10) + '0';
		n /= 10;
		fill(ptr, n, --x);
	}
	return (ptr);
}

static char	*ft_itoa_u(unsigned int n)
{
	char			*ptr;
	unsigned int	i;
	int				x;

	x = 0;
	i = n;
	n /= 10;
	x++;
	while (n != 0)
	{
		n /= 10;
		x++;
	}
	ptr = (char *)malloc((x + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[x] = '\0';
	x--;
	return (fill(ptr, i, x));
}

int	print_u(unsigned int n)
{
	char	*str;
	int		len;

	len = 0;
	str = ft_itoa_u(n);
	if (str == NULL)
		return (-1);
	len += print_str(str);
	free(str);
	return (len);
}
