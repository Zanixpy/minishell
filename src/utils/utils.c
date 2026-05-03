/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:18:48 by omawele           #+#    #+#             */
/*   Updated: 2026/04/29 11:06:28 by omawele          ###   ########.fr       */
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

int check_quote_count(char *s)
{
	char quote;
	int check_quote;
	int i;

	i = 0;
	check_quote = 0;
	quote = 0;
	while (s[i]) 
	{
		quote = s[i];
		if ((s[i] == QUOTE || s[i] == DQUOTE) && check_quote % quote == 0)
		{
			if (check_quote > 0)
				check_quote -= s[i];
			else
				check_quote += s[i];
		}
		i++;
	}
	if (check_quote % QUOTE == 0)
		return (check_quote / QUOTE);
	return (check_quote / DQUOTE);
}

size_t array_size(char **tab)
{
	int count;

	count = 0;
	while (tab[count])
		count++;
	return (count);	
}


