/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:21:03 by omawele           #+#    #+#             */
/*   Updated: 2026/04/28 19:44:33 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_char_tab_n(char ***tab, int n)
{
	if (!(*tab))
		return;
	while (n >= 0)
	{
		free((*tab)[n]);
		n--;
	}
	free(*tab);
}

void	free_char_tab(char ***tab)
{
	int n;

	if (!(*tab))
		return;
	n = 0;
	while ((*tab)[n])
	{
		free((*tab)[n]);
		n++;
	}
	free(*tab);
}

void free_str(char **s)
{
	if (*s)
		free(*s);
}

char **create_tab(char *str)
{
	char **tab;

	tab = ft_calloc(2, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(str);
	if (!(tab[0]))
		return (free(tab), NULL);
}

char **add_element_in_array(char **tab, char *str)
{
	char **tmp;
	int length;
	int i;

	length = array_size(tab);
	tmp = ft_calloc(length + 2, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < length) 
	{
		tmp[i] = ft_strdup(tab[i]);
		if (!(tmp[i]))
			return (free_char_tab_n(&tmp, i), NULL);
		i++;
	}
	tmp[i] = ft_strdup(str);
	if (!(tmp[i]))
		return (free_char_tab_n(&tmp, i), NULL);
	return (tmp);
}



