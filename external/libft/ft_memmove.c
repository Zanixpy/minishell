/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:38:19 by omawele           #+#    #+#             */
/*   Updated: 2025/11/11 12:17:20 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, unsigned int n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned int	i;

	if (!dest && !src)
		return (0);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (d > s)
	{
		while ((n - i) > 0)
		{
			d[n - 1 - i] = s[n - 1 - i];
			i++;
		}
		return (dest);
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
