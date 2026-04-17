/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:14:13 by omawele           #+#    #+#             */
/*   Updated: 2025/11/09 16:54:07 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(const char *s, const char *little, size_t len, size_t i)
{
	size_t	j;

	j = 0;
	while (s[j] && s[j] == *little && i < len)
	{
		j++;
		little++;
		if (*little == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (big[j] && i < len)
	{
		if (ft_search(big + j, little, len, i) == 1)
			return ((char *)(big + j));
		i++;
		j++;
	}
	return (NULL);
}
