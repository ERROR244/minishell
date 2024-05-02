/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:31:36 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/10 21:01:47 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len] == (char)c)
			return ((char *)(&s[len]));
		len--;
	}
	if (s[len] == (char)c)
		return ((char *)(&s[len]));
	return (NULL);
}
// // #include<string.h>
// int main ()
// {
//     char d[] = "";
//     printf("%s\n",ft_strrchr(d, '\0'));
//     printf("%s\n",strrchr(d, '\0'));
// }