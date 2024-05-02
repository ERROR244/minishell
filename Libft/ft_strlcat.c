/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:20:44 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/17 13:50:39 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;
	size_t	dst_length;
	size_t	src_length;

	i = 0;
	src_length = ft_strlen(src);
	if (size == 0 && dst == NULL)
		return (src_length);
	dst_length = ft_strlen(dst);
	if (dst_length < size)
		res = dst_length + src_length;
	else
		res = size + src_length;
	if (size == 0)
		return (res);
	while (src[i] && dst_length + i < size - 1)
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	return (res);
}
