/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:18:48 by omawele           #+#    #+#             */
/*   Updated: 2026/04/28 20:20:40 by omawele          ###   ########.fr       */
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

char *extract_in_quote(char *s)
{
	char *tmp;
	int len;
	int i;

	len = ft_strlen(s) - 2;
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len) 
	{
		tmp[i] = s[i + 1];
		i++;
	}
	return (tmp);	
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

char *clean_str(char *s)
{
    char *tmp;
	
	if (is_var(s))
		tmp = expand_var(s);
	else if (is_quoted(s))
		tmp = extract_in_quote(s);
	else if (check_quote_count(s))
		tmp = 
	else
	 	tmp = ft_strdup(s);
	if (!tmp)
		return (NULL);
	return (tmp);
}

size_t array_size(char **tab)
{
	int count;

	count = 0;
	while (tab[count])
		count++;
	return (count);	
}


