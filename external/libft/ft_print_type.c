/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:39:19 by omawele           #+#    #+#             */
/*   Updated: 2025/12/02 18:23:27 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char(char c, int *count)
{
	*count += write(1, &c, 1);
}

void	ft_print_int(long n, int *count)
{
	char	c;

	c = 0;
	if (n < 0)
	{
		*count += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_print_int((n / 10), count);
	c = '0' + (n % 10);
	*count += write(1, &c, 1);
}

void	ft_print_hexa(long n, int *count, char mode)
{
	char	c;

	c = 0;
	if (n < 0)
	{
		*count += write(1, "-", 1);
		n = -n;
	}
	if (n > 15)
		ft_print_hexa((n / 16), count, mode);
	c = ft_hexa((n % 16), mode);
	*count += write(1, &c, 1);
}

void	ft_print_string(char *s, int *count)
{
	if (!s)
	{
		*count += write(1, "(null)", 6);
		return ;
	}
	while (*s)
	{
		*count += write(1, s, 1);
		s++;
	}
}

void	ft_print_pointer(void *ptr, int *count)
{
	uintptr_t	ptr_long;

	if (!ptr)
	{
		*count += write(1, "(nil)", 5);
		return ;
	}
	ptr_long = (uintptr_t)ptr;
	ft_print_string("0x", count);
	ft_print_hexa(ptr_long, count, 'x');
}
