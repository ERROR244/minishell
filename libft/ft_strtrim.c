/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:29:39 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/08 20:08:31 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checker(char const *s, char const c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newone;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1)
	{
		if (checker(set, *s1) == 1)
			s1++;
		else
			break ;
	}
	len = ft_strlen(s1);
	while (len > 0)
	{
		if (checker(set, s1[len - 1]) == 1)
			len--;
		else
			break ;
	}
	newone = (char *)malloc((len + 1) * sizeof(char));
	if (!newone)
		return (NULL);
	ft_strlcpy(newone, s1, len + 1);
	return (newone);
}
