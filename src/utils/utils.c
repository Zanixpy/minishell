/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:18:48 by omawele           #+#    #+#             */
/*   Updated: 2026/05/20 12:23:42 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	int n;

	n = 0;
	while (s1[n] || s2[n]) 
	{
		if (s1[n] != s2[n])
			return (1);
		n++;
	}
	return (0);
}

size_t array_size(char **tab)
{
	int count;

	count = 0;
	while (tab[count])
		count++;
	return (count);	
}


