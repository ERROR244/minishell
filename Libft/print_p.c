/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:55:37 by ksohail-          #+#    #+#             */
/*   Updated: 2024/01/31 21:25:45 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_hex(char *str, int i)
{
	int	x;

	i--;
	while (i >= 0)
	{
		x = print_ch(str[i]);
		if (x < 0)
			return (x);
		i--;
	}
	return (x);
}

static int	static_print_x(uintptr_t n, char c)
{
	char			str[40];
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (n == 0)
		return (print_ch('0'));
	while (n != 0)
	{
		i = n % 16;
		if (i < 10)
			i = i + '0';
		else if (c == 'X')
			i = i + 'A' - 10;
		else if (c == 'x')
			i = i + 'a' - 10;
		str[j++] = i;
		n = n / 16;
	}
	str[j] = '\0';
	if (print_hex(str, j) < 0)
		return (-1);
	return (ft_strlen(str));
}

int	print_p(void *ptr)
{
	uintptr_t	address;
	int			len;
	int			k;

	len = 0;
	address = (uintptr_t)ptr;
	k = print_ch('0');
	if (k < 0)
		return (k);
	k = print_ch('x');
	if (k < 0)
		return (k);
	len = static_print_x(address, 'x');
	if (len < 0)
		return (len);
	return (len + 2);
}
