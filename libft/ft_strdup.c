/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:30:38 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/10 21:00:20 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*copie;

	i = 0;
	len = ft_strlen(s);
	copie = (char *)malloc((len + 1) * sizeof(char));
	if (copie == NULL)
		return (NULL);
	while (len > i)
	{
		copie[i] = s[i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

//  int main ()
//  {
//    const char s[] = "oualid";
//    printf("%s\n",ft_strdup(s));
//    printf("%s",strdup(s));
//  }