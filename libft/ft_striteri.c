/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:00:23 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/13 16:35:12 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// void fss(unsigned int i, char *c)
// {
// 	if (*c >= 'a' && *c <= 'z')
// 		*c -= 32;
// }
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// int main()
// {
// 	char s[] = "Hello world!";
// 	ft_striteri(s, fss);
// 	printf("%s", s);
// 	return 0;
// }