/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:47:38 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/02 17:46:21 by error01          ###   ########.fr       */
=======
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:47:38 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/09 08:26:40 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD
int ft_no_st_len(const char *str)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9)
			size++;
		i++;
	}
	return (size);
}


=======
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;
	int		k;
	int		len;

<<<<<<< HEAD
	len = ft_no_st_len(s);
=======
	len = ft_strlen(s);
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
	i = 0;
	k = 0;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
<<<<<<< HEAD
		if (s[k] != 32 && s[k] != 9)
		{
			ptr[i] = s[k];
			i++;
		}
=======
		ptr[i] = s[k];
		i++;
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
		k++;
	}
	ptr[i] = '\0';
	return (ptr);
}
