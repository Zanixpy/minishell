/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:23:21 by omawele           #+#    #+#             */
/*   Updated: 2026/06/07 21:51:13 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*add_char_in_str(char *s, int pos, char c)
{
	char	*tmp;
	int		length;
	int		i;
	int		j;

	length = ft_strlen(s) + 1;
	tmp = ft_calloc(length + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < length)
	{
		if (i == pos)
			tmp[i] = c;
		else
			tmp[i] = s[j++];
		i++;
	}
	return (tmp);
}

static int	is_valid_meta(char *s, int pos, char meta)
{
	if (meta == GREAT)
	{
		if (s[pos] != GREAT)
			return (1);
		if (pos >= 2)
		{
			if (s[pos - 2] == GREAT && s[pos - 1] == GREAT && s[pos] == GREAT)
				return (1);
		}
	}
	else if (meta == LESS)
	{
		if (s[pos] != LESS)
			return (1);
		if (pos >= 2)
		{
			if (s[pos - 2] == LESS && s[pos - 1] == LESS && s[pos] == LESS)
				return (1);
		}
	}
	return (0);
}

static int	is_paste_word(char *s)
{
	int		i;
	int		is_meta_or_char;
	char	meta;

	is_meta_or_char = 0;
	if (*s == GREAT || *s == LESS || *s == PIPE)
	{
		is_meta_or_char = 1;
		meta = *s;
	}
	i = 0;
	while (s[i] && s[i] != SPACE)
	{
		if (is_meta_or_char)
		{
			if ((meta == PIPE && i != 0) || is_valid_meta(s, i, meta))
				return (i);
		}
		else if (!is_meta_or_char && (s[i] == GREAT || s[i] == LESS
				|| s[i] == PIPE))
			return (i);
		i++;
	}
	return (0);
}

static void	rebuild_prompt(char **prompt, int *pos)
{
	char	*tmp;
	int		ret;

	ret = is_paste_word(*prompt + *pos);
	if (ret == 0)
		return ;
	tmp = add_char_in_str(*prompt, ret + *pos, SPACE);
	free_str(prompt);
	if (!tmp)
		return ;
	*prompt = tmp;
	*pos += ret;
}

char	*clean_prompt(char *prompt)
{
	int		i;
	char	quote;

	prompt = ft_strdup(prompt);
	if (!prompt)
		return (NULL);
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == QUOTE || prompt[i] == DQUOTE)
		{
			quote = prompt[i];
			if (ft_strchr(prompt + ++i, quote))
				while (prompt[i] && prompt[i++] != quote);
		}
		else if (is_paste_word(prompt + i))
		{
			rebuild_prompt(&prompt, &i);
			if (!prompt)
				return (NULL);
		}
		else
			i++;
	}
	return (prompt);
}
