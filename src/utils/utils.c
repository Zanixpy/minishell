/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:18:48 by omawele           #+#    #+#             */
/*   Updated: 2026/06/15 16:27:28 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	n;

	n = 0;
	while (s1[n] || s2[n])
	{
		if (s1[n] != s2[n])
			return (1);
		n++;
	}
	return (0);
}

int	array_size(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
		count++;
	return (count);
}

int	is_skip(char *prompt, t_shell *shell)
{
	char	*tmp;

	if (!(*prompt))
		return (1);
	add_history(prompt);
	if (is_space(prompt))
	{
		shell->exit_status = 0;
		return (1);
	}
	tmp = ft_strtrim(prompt, " ");
	if (!tmp)
		return (ERRMALLOC);
	else if (!ft_strcmp(tmp, "!") || !ft_strcmp(tmp, ":") || !ft_strcmp(tmp,
			"#"))
	{
		if (!ft_strcmp(tmp, "!"))
			shell->exit_status = 1;
		else
			shell->exit_status = 0;
		return (free(tmp), 1);
	}
	free(tmp);
	return (0);
}

int	is_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != SPACE && (str[i] < 9 || str[i] > 13))
			return (0);
		i++;
	}
	return (1);
}

int	is_unexpand_char(char c)
{
	if (c == '+' || c == ',' || c == '=' || c == ':' || c == SPACE)
		return (1);
	return (0);
}
