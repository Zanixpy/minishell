/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:21:03 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 17:24:10 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	free_char_tab_n(char ***tab, int n)
{
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

	n = 0;
	while ((*tab)[n])
	{
		free((*tab)[n]);
		n++;
	}
	free(*tab);
}


