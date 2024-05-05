/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:47:13 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/01 01:39:21 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_and_print(int *return_len, char *str, va_list lst)
{
	if (ft_strncmp("%c", str, 2) == 0)
		*return_len = print_ch(va_arg(lst, int));
	else if (ft_strncmp("%d", str, 2) == 0)
		*return_len = print_i_d(va_arg(lst, int));
	else if (ft_strncmp("%i", str, 2) == 0)
		*return_len = print_i_d(va_arg(lst, int));
	else if (ft_strncmp("%p", str, 2) == 0)
		*return_len = print_p(va_arg(lst, void *));
	else if (ft_strncmp("%s", str, 2) == 0)
		*return_len = print_str(va_arg(lst, char *));
	else if (ft_strncmp("%u", str, 2) == 0)
		*return_len = print_u(va_arg(lst, unsigned int));
	else if (ft_strncmp("%x", str, 2) == 0)
		*return_len = print_x(va_arg(lst, unsigned long), 'x');
	else if (ft_strncmp("%X", str, 2) == 0)
		*return_len = print_x(va_arg(lst, unsigned long), 'X');
	else if (ft_strncmp("%%", str, 2) == 0)
		*return_len = print_ch('%');
	else if (str[1] != '\0')
		*return_len = print_ch(str[1]);
	else
		*return_len = 0;
}

static int	to_check_ptr(const char *str, int i, va_list lst)
{
	char	ptr[3];
	int		return_len;

	return_len = 0;
	ptr[0] = str[i];
	ptr[1] = str[i + 1];
	ptr[2] = '\0';
	check_and_print(&return_len, ptr, lst);
	return (return_len);
}

static int	function(int *k, int i, const char *str, va_list lst)
{
	if (str[i] == '%' && str[i + 1] != '\0')
	{
		*k = to_check_ptr(str, i, lst);
		i += 2;
	}
	else if (str[i] != '%')
		*k = print_ch(str[i++]);
	else
		i++;
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		return_len;
	int		i;
	int		k;
	va_list	lst;

	va_start(lst, str);
	i = 0;
	return_len = 0;
	while (str[i] != '\0')
	{
		k = 0;
		i = function(&k, i, str, lst);
		if (k < 0)
		{
			va_end(lst);
			return (k);
		}
		return_len += k;
	}
	va_end(lst);
	return (return_len);
}
