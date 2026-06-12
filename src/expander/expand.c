/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 11:48:52 by omawele           #+#    #+#             */
/*   Updated: 2026/06/12 14:48:21 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*build_var(char *s, int *pos)
{
	char	*tmp;
	int		sub_len;

	sub_len = 0;
	if (ft_isdigit(s[*pos]) || is_special_char(s[*pos]))
	{
		sub_len++;
		tmp = ft_substr(s, *pos, sub_len);
	}
	else
	{
		while (ft_isalnum(s[*pos + sub_len]) || s[*pos + sub_len] == '_')
			sub_len++;
		tmp = ft_substr(s, *pos, sub_len);
	}
	if (!tmp)
		return (NULL);
	*pos += sub_len;
	return (tmp);
}

static char	*convert_var(char *s, int *pos, int exit_status, char **envp)
{
	char	*val;
	char	*tmp;

	tmp = build_var(s, pos);
	if (!tmp)
		return (NULL);
	if (!ft_strcmp(tmp, "?"))
	{
		free(tmp);
		tmp = ft_itoa(exit_status);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	val = get_env_value(tmp, envp);
	free(tmp);
	if (!val)
		tmp = ft_calloc(1, sizeof(char));
	else
		tmp = val;
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*rebuild_str(char **s, int start_var, int end_var, char *var)
{
	char	*tmp;
	int		length;
	int		i;
	int		j;

	length = ft_strlen(*s) - (end_var - start_var) + ft_strlen(var);
	tmp = ft_calloc(length + 1, sizeof(char));
	if (!tmp)
		return (free_str(s), NULL);
	i = 0;
	j = 0;
	while (i < length)
	{
		if (j == start_var)
		{
			fill_var_in_str(&tmp, &i, var);
			j = end_var;
		}
		else
		{
			tmp[i] = (*s)[j++];
			i++;
		}
	}
	return (tmp);
}

static void	format_string(char **s, int *i, int exit_status, char **envp)
{
	char	*var;
	char	*tmp;
	int		end_var;

	end_var = *i + 1;
	var = convert_var(*s, &end_var, exit_status, envp);
	if (!var)
		return (free_str(s));
	tmp = rebuild_str(s, *i, end_var, var);
	free(var);
	if (!tmp)
		return (free_str(s));
	free(*s);
	*s = tmp;
	(*i)--;
}

char	*expand_str(char *s, int exit_status, char **envp)
{
	int	i;
	int	is_dquote;

	s = ft_strdup(s);
	if (!s)
		return (NULL);
	i = 0;
	is_dquote = 1;
	while (s[i])
	{
		if (s[i] == DQUOTE)
			is_dquote = -is_dquote;
		else if (s[i] == QUOTE && is_dquote == 1)
			while (s[++i] && s[i] != QUOTE)
				;
		else if (s[i] == DOLLAR && s[i + 1] && !is_unexpand_char(s[i + 1]))
		{
			format_string(&s, &i, exit_status, envp);
			if (!s)
				return (NULL);
		}
		i++;
	}
	return (s);
}
