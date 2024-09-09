/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
=======
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:51:06 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/17 14:15:47 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
