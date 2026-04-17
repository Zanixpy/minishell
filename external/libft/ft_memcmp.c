/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:33:48 by omawele           #+#    #+#             */
/*   Updated: 2025/11/07 15:36:02 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*first;
	const unsigned char	*second;
	size_t				size;

	first = (const unsigned char *)s1;
	second = (const unsigned char *)s2;
	size = 0;
	while (size < n)
	{
		if (first[size] < second[size])
			return (-1);
		else if (first[size] > second[size])
			return (1);
		size++;
	}
	return (0);
}
