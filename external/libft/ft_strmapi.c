/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:11:00 by omawele           #+#    #+#             */
/*   Updated: 2025/11/07 17:11:59 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		n;

	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	n = 0;
	while (str[n])
	{
		str[n] = (*f)(n, str[n]);
		n++;
	}
	return (str);
}
