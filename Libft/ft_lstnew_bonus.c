/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
=======
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:17:22 by ksohail-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/05 15:41:36 by ksohail-         ###   ########.fr       */
=======
/*   Updated: 2024/05/17 14:15:19 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n_node;

	n_node = (t_list *)malloc(sizeof(struct s_list));
	if (n_node == NULL)
		return (NULL);
	n_node->content = content;
	n_node->next = NULL;
	return (n_node);
}
