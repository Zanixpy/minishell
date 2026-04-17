/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:39:10 by omawele           #+#    #+#             */
/*   Updated: 2025/12/18 19:51:24 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_hexa(int pos, char mode)
{
	char	*hexa_lower;
	char	*hexa_upper;

	hexa_lower = "0123456789abcdef";
	hexa_upper = "0123456789ABCDEF";
	if (mode == 'X')
		return (hexa_upper[pos]);
	return (hexa_lower[pos]);
}
