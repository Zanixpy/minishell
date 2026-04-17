/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:31:51 by omawele           #+#    #+#             */
/*   Updated: 2025/11/07 16:33:08 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cp;
	int		n;

	n = 0;
	while (s[n])
		n++;
	cp = malloc(sizeof(char) * (n + 1));
	if (cp == NULL)
		return (NULL);
	n = 0;
	while (s[n])
	{
		cp[n] = s[n];
		n++;
	}
	cp[n] = '\0';
	return (cp);
}
