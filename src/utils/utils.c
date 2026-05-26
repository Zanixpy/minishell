/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:18:48 by omawele           #+#    #+#             */
/*   Updated: 2026/05/26 11:56:31 by omawele          ###   ########.fr       */
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

int is_skip(char *prompt)
{
	char *tmp;
	
	if (!prompt)
		return (1);
	if (is_space(prompt))
		return (1);
	tmp = ft_strtrim(prompt, " ");
	if (!tmp)
		return (ERRMALLOC);
	if (!ft_strcmp(tmp, "!") || !ft_strcmp(tmp, ":"))
		return (1);
	return (0);
}

int is_space(char *str)
{
    while (*str) 
    {
        if (*str != SPACE && (*str < 9 ||*str > 13))
            return (0);
        str++;
    }
    return (1);
}


