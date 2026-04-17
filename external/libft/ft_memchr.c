/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:24:28 by omawele           #+#    #+#             */
/*   Updated: 2025/11/07 15:32:38 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, unsigned int n)
{
	unsigned char	*d;
	unsigned char	tmp;
	unsigned int	i;

	d = (unsigned char *)s;
	tmp = c;
	i = 0;
	while (i < n)
	{
		if (d[i] == tmp)
			return (d + i);
		i++;
	}
	return (NULL);
}
