/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
=======
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:29:17 by ksohail-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/06 11:18:35 by ksohail-         ###   ########.fr       */
=======
/*   Updated: 2024/05/17 14:18:24 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = lst;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}
