/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:22:15 by omawele           #+#    #+#             */
/*   Updated: 2026/06/15 16:26:29 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(char *str, int i)
{
	char	*quote;
	int		count;

	count = 0;
	while (str[i])
	{
		if (str[i] != SPACE)
		{
			count++;
			while (str[i] && str[i] != SPACE)
			{
				if (str[i] == QUOTE || str[i] == DQUOTE)
				{
					quote = ft_strchr(str + i + 1, str[i]);
					if (quote)
						i += (intptr_t)quote - (intptr_t)(str + i);
				}
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

static int	malloc_token(char ***tokens, char *s, int i, int *j)
{
	int		len;
	int		o;
	char	*quote;

	len = 0;
	while (s[*j + len] && s[*j + len] != SPACE)
	{
		if (s[*j + len] == QUOTE || s[*j + len] == DQUOTE)
		{
			quote = ft_strchr(s + *j + len + 1, s[*j + len]);
			if (quote)
				len += (intptr_t)quote - (intptr_t)(s + *j + len);
		}
		len++;
	}
	(*tokens)[i] = ft_calloc(len + 1, sizeof(char));
	if (!(*tokens)[i])
		return (1);
	o = -1;
	while (++o < len)
		(*tokens)[i][o] = s[*j + o];
	*j += len;
	return (0);
}

static int	tokenization(char ***tokens, char *prompt, int nb_words)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nb_words)
	{
		if (prompt[j] != SPACE)
		{
			if (malloc_token(tokens, prompt, i, &j))
				return (free_char_tab_n(tokens, i - 1), 1);
			i++;
		}
		else
			j++;
	}
	return (0);
}

static char	**clean_tokens(char **tokens)
{
	char	**temp;
	int		length;
	int		i;

	length = array_size(tokens);
	temp = ft_calloc(length + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < length)
	{
		temp[i] = ft_strtrim(tokens[i], " ");
		if (!temp[i])
			free_char_tab_n(&temp, i - 1);
		i++;
	}
	return (temp);
}

char	**lexer(char *prompt)
{
	char	**temp;
	char	**tokens;
	int		nb_words;

	nb_words = count_words(prompt, 0);
	temp = ft_calloc(nb_words + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	if (tokenization(&temp, prompt, nb_words))
		return (NULL);
	tokens = clean_tokens(temp);
	if (!tokens)
		return (free_char_tab(&temp), NULL);
	free_char_tab(&temp);
	return (tokens);
}
