/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:37:17 by ohassani          #+#    #+#             */
/*   Updated: 2023/11/10 21:09:25 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*rslt;

	i = 0;
	len = ft_strlen(s);
	rslt = (char *)malloc((len + 1) * sizeof(char));
	if (rslt == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		rslt[i] = f(i, s[i]);
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}
// char fs(unsigned int i, char c)
// {
// 	if(c >= 'a' && c <= 'z')
// 		return(c -= 32);
// 	return(c);	
// }
// #include<stdio.h>
// int main ()
// {
// 	char s[] = "oualid";
// 	char *res  = ft_strmapi(s, fs);
// 	printf("%s",res);
// }
