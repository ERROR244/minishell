/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:37:52 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/13 15:26:28 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*pointer;

	i = 0;
	pointer = (unsigned char *)str;
	while (i < len)
	{
		pointer[i] = (unsigned char )c;
		i++;
	}
	return (pointer);
}
/*int main () {
	int ii[] = {0, 0 , 0, 0};
	ft_memset(ii, 8, 1);
	ft_memset(ii + 1, 7 , 2);

	for(int i = 0; i < 4 ; i++)
		printf("%d   ", ii[i]);

}*/
