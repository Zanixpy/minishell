/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:43:37 by omawele           #+#    #+#             */
/*   Updated: 2025/11/08 11:47:24 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s)
{
	unsigned int	n;

	n = 0;
	while (*s)
	{
		n++;
		s++;
	}
	return (n);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	n;
	char			*tmp;

	if ((start == 0 && len == 0) || start >= ft_len(s))
	{
		tmp = malloc(sizeof(char));
		if (tmp == NULL)
			return (NULL);
		tmp[0] = '\0';
		return (tmp);
	}
	if (len > ft_len(s + start))
		len = ft_len(s + start);
	tmp = malloc((len + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	n = 0;
	while (s[start] && n < len)
	{
		tmp[n] = s[start];
		n++;
		start++;
	}
	tmp[n] = '\0';
	return (tmp);
}
