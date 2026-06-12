/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:22:15 by omawele           #+#    #+#             */
/*   Updated: 2026/06/12 14:57:34 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_words(char *str)
{
	size_t	count;
	size_t	i;
	size_t  is_word;
	int	quote;

	count = 0;
	i = -1;
	is_word = 0;
	while (str[++i])
	{
		if (str[i] != SPACE)
		{
			if (is_word == 0)
				count += 1;		
			is_word = 1;
			if (str[i] == QUOTE || str[i] == DQUOTE)
			{
				quote = str[i];
				while (str[++i] && str[i] != quote);
			}			
		} 
		if (str[i] == SPACE)
			is_word = 0;
	}
	return (count);
}

static int	malloc_token(char ***tokens, char *prompt, size_t *i, size_t *j)
{
	size_t	length;
	size_t	o;
	int		is_quoted;

	length = 0;
	while (prompt[*j + length] && prompt[*j + length] != SPACE)
	{
		if (prompt[*j + length] == QUOTE || prompt[*j + length] == DQUOTE)
		{
			is_quoted = prompt[*j];
			while (prompt[*j + 1 + length] && prompt[*j + 1 + length++] != is_quoted);
		}
		length++;
	}
	(*tokens)[*i] = ft_calloc(length + 1, sizeof(char));
	if (!(*tokens)[*i])
		return (1);
	o = -1;
	while (++o < length)
		(*tokens)[*i][o] = prompt[*j + o];
	(*i)++;
	*j += length;
	return (0);
}

static int	tokenization(char ***tokens, char *prompt, size_t nb_words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < nb_words)
	{
		if (prompt[j] != SPACE)
		{
			if (malloc_token(tokens, prompt, &i, &j))
				return (free_char_tab_n(tokens, i - 1), 1);
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
	size_t	nb_words;

	nb_words = count_words(prompt);
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
