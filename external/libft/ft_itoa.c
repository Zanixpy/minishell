/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:42:47 by omawele           #+#    #+#             */
/*   Updated: 2025/11/07 17:36:53 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_isnegative(long *nb, int *sign)
{
	if (*nb < 0)
	{
		*sign = 1;
		*nb *= -1;
	}
	else
		*sign = 0;
}

static void	ft_len(int *n, int *size)
{
	int	nb;
	int	len;

	nb = *n;
	len = *size;
	nb /= 10;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	*n = nb;
	*size = len;
}

char	*ft_itoa(int n)
{
	char	*str;
	long	tmp;
	int		size;
	int		sign;

	size = 1;
	tmp = (long)n;
	ft_isnegative(&tmp, &sign);
	ft_len(&n, &size);
	size += sign;
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	while (size--)
	{
		str[size] = '0' + (tmp % 10);
		tmp /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
