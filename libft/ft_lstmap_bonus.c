/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:20:33 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/22 14:15:18 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	if (!lst)
		return (NULL);
	new_lst = 0;
	while (lst)
	{
		new_elem = ft_lstnew((*f)(lst->content));
		ft_lstadd_back(&new_lst, new_elem);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (new_lst);
}
