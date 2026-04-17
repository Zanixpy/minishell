/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:42:54 by omawele           #+#    #+#             */
/*   Updated: 2026/03/24 20:24:16 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*p;

	p = *lst;
	if (p == NULL)
	{
		*lst = node;
		return ;
	}
	while (p != NULL)
	{
		if (p->next == NULL)
		{
			p->next = node;
			return ;
		}
		p = p->next;
	}
}
