/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:30:31 by omawele           #+#    #+#             */
/*   Updated: 2025/11/07 16:31:33 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	src;

	src = c;
	while (*s)
	{
		if (*s == src)
			return ((char *)s);
		s++;
	}
	if (*s == src)
		return ((char *)s);
	return (NULL);
}
