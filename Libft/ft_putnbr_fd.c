/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:56:29 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/16 18:39:20 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_function(int nb, int fd)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n <= 9)
	{
		ft_putchar_fd(n + '0', fd);
		return ;
	}
	if (n != 0)
	{
		ft_function(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd >= 0)
		ft_function(n, fd);
}
