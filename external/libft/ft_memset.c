/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:40:02 by omawele           #+#    #+#             */
/*   Updated: 2025/11/11 15:17:29 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*d;
	size_t			n;

	d = (unsigned char *)pointer;
	n = 0;
	while (n < count)
	{
		d[n] = value;
		n++;
	}
	return (d);
}
