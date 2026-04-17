/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:51:47 by omawele           #+#    #+#             */
/*   Updated: 2025/11/08 11:52:34 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	src;

	src = c;
	tmp = NULL;
	while (*s)
	{
		if (*s == src)
			tmp = (char *)s;
		s++;
	}
	if (*s == src)
		return ((char *)s);
	return (tmp);
}
