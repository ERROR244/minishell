/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   ft_ft_lstmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:09:19 by ksohail-          #+#    #+#             */
/*   Updated: 2023/11/12 14:01:05 by ksohail-         ###   ########.fr       */
=======
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:15:37 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/17 14:15:42 by ksohail-         ###   ########.fr       */
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_list;
	t_list	*new;
	void	*content_res;

	n_list = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{
		content_res = f(lst->content);
		new = ft_lstnew(content_res);
		if (new == NULL)
		{
			free(content_res);
			free(new);
			ft_lstclear(&n_list, del);
			return (NULL);
		}
		ft_lstadd_back(&n_list, new);
		lst = lst->next;
	}
	return (n_list);
}
