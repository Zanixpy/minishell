/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:47:12 by omawele           #+#    #+#             */
/*   Updated: 2025/11/11 12:11:48 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char ***tab, int n)
{
	while (n >= 0)
	{
		free((*tab)[n]);
		n--;
	}
	free(*tab);
}

static int	count_words(const char *s, char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && n == 0)
		{
			i++;
			n = 1;
		}
		else if (*s == c && n == 1)
			n = 0;
		s++;
	}
	return (i);
}

static size_t	ft_len(const char *str, char c)
{
	int	n;

	n = 0;
	while (*str != c && *str)
	{
		n++;
		str++;
	}
	return (n);
}

static	void	conca(char ***tab, const char **s, int *pos, int len)
{
	const char	*str;
	int			n;
	int			i;

	n = *pos;
	i = 0;
	str = *s;
	while (i < len)
	{
		(*tab)[n][i] = *str;
		str++;
		i++;
	}
	*s = str;
	*pos = n + 1;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;
	int		n;

	words = count_words(s, c);
	tab = ft_calloc((words + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	n = 0;
	while (n < words)
	{
		if (*s != c)
		{
			tab[n] = ft_calloc((ft_len(s, c) + 1), sizeof(char));
			if (tab[n] == NULL)
			{
				ft_free(&tab, n - 1);
				return (NULL);
			}
			conca(&tab, &s, &n, ft_len(s, c));
		}
		else
			s++;
	}
	return (tab);
}
