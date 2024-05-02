/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:47:38 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/02 17:42:17 by error01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_no_st_len(const char *str)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if ((str[i] != 32 && str[i] != 9) || ft_isalpha(s[i+1]) == 1)
			size++;
		i++;
	}
	return (size);
}


char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;
	int		k;
	int		len;

	len = ft_no_st_len(s);
	i = 0;
	k = 0;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		if ((s[k] != 32 && s[k] != 9) || ft_isalpha(s[k+1]) == 1)
		{
			ptr[i] = s[k];
			i++;
		}
		k++;
	}
	ptr[i] = '\0';
	free(s);
	return (ptr);
}
