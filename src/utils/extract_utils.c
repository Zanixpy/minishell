/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:05:10 by omawele           #+#    #+#             */
/*   Updated: 2026/05/29 09:18:21 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	rebuild_str(char **s, int start_quote, int end_quote)
{
	char	*tmp;
	int		length;
	int		i;
	int		j;

	length = ft_strlen(*s) - 2;
	tmp = ft_calloc(length + 1, sizeof(char));
	if (!tmp)
		return (free_str(s));
	i = 0;
	j = 0;
	while (i < length)
	{
		if (j == start_quote)
			j++;
		if (j == end_quote)
			j++;
		tmp[i] = (*s)[j];
		i++;
		j++;
	}
	free(*s);
	*s = tmp;
}

static int	is_valid_quote(char *s, char quote, int pos)
{
	int	i;

	i = pos + 1;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote && pos != i)
		return (i);
	return (0);
}

static char	*strremove_quotes(char *s)
{
	int	i;
	int	ret;

	s = ft_strdup(s);
	if (!s)
		return (NULL);
	i = -1;
	while (s[++i])
	{
		if ((s[i] == QUOTE || s[i] == DQUOTE))
		{
			ret = is_valid_quote(s, s[i], i);
			if (ret)
			{
				rebuild_str(&s, i, ret);
				if (!s)
					return (NULL);
				if (ret < 2)
					i = -1;
				else
					i = ret - 3;
			}
		}
	}
	return (s);
}

void	fill_var_in_str(char **tmp, int *i, char *var)
{
	if (*var == 0)
		return ;
	while (*var)
	{
		(*tmp)[*i] = *var;
		*i += 1;
		var++;
	}
}

char	*clean_str(char *s, int is_delim, int exit_status)
{
	char	*tmp;
	char	*temp_str;

	if (is_delim)
		temp_str = ft_strdup(s);
	else
		temp_str = expand_str(s, exit_status);
	if (!temp_str)
		return (NULL);
	if (*temp_str == '\0')
		return (temp_str);
	if (ft_strchr(temp_str, QUOTE) || ft_strchr(temp_str, DQUOTE))
		tmp = strremove_quotes(temp_str);
	else
		tmp = ft_strdup(temp_str);
	free(temp_str);
	if (!tmp)
		return (NULL);
	return (tmp);
}
