/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:45:45 by ksohail-          #+#    #+#             */
/*   Updated: 2024/01/31 21:25:58 by ksohail-         ###   ########.fr       */
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

int	print_x(unsigned int n, char c)
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
