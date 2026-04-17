/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:44:44 by omawele           #+#    #+#             */
/*   Updated: 2026/03/24 20:24:35 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *node)
{
	t_list	*p;

	p = *lst;
	if (p == NULL)
	{
		*lst = node;
		return ;
	}
	*lst = node;
	node->next = p;
}
