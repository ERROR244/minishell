/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:06:15 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/10 16:52:09 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	positive(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	counter(int n)
{
	int	digit;

	digit = 0;
	if (n <= 0)
		digit++;
	while (n != 0)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	long int	i;

	i = counter(n);
	ptr = malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	if (n < 0)
		ptr[0] = '-';
	else if (n == 0)
		ptr[0] = '0';
	while (n != 0)
	{
		i--;
		ptr[i] = positive(n % 10) + 48;
		n = n / 10;
	}
	return (ptr);
}

// int main ()
// {
//   char *res = ft_itoa(0);
//   printf("%s", res);
// }