/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:48:45 by omawele           #+#    #+#             */
/*   Updated: 2025/11/11 12:15:25 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tab;
	t_list	*tmp;
	void	*result;

	if (!lst)
		return (NULL);
	result = (*f)(lst->content);
	tab = ft_lstnew(result);
	if (tab == NULL)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		result = (*f)(lst->content);
		tmp = ft_lstnew(result);
		if (tmp == NULL)
		{
			ft_lstclear(&tab, del);
			return (NULL);
		}
		ft_lstadd_back(&tab, tmp);
		lst = lst->next;
	}
	return (tab);
}
