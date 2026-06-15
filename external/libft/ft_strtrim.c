/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:47:36 by omawele           #+#    #+#             */
/*   Updated: 2026/06/12 16:04:17 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chr(char c, char const *set)
{
	unsigned int	n;

	n = 0;
	while (set[n])
	{
		if (ft_toupper(c) == set[n] || ft_tolower(c) == set[n] || c == set[n])
			return (1);
		n++;
	}
	return (0);
}

static char	*empty(void)
{
	char	*tmp;

	tmp = malloc(sizeof(char));
	if (tmp == NULL)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}

char    *ft_strtrim(char const *s1, char const *set)
{
    char    *tmp;
    int     j;
    int     i;
    int     n;

    if (!s1 || !set)
        return (NULL);
    i = ft_strlen(s1);
    if (!i)
        return (empty());
    j = 0;
    while (s1[j] && chr(s1[j], set))
        j++;      
    while (i > j && chr(s1[i - 1], set))
        i--;    
    i -= j;
    if (i <= 0)
        return (empty());
    tmp = ft_calloc((i + 1), sizeof(char));
    if (!tmp)
        return (NULL);
    n = -1;
    while (++n < i)
        tmp[n] = s1[j++];
    return (tmp);
}
