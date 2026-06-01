/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:58:02 by omawele           #+#    #+#             */
/*   Updated: 2026/05/29 09:38:30 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int is_bic(char *str)
{
	if (!ft_strcmp("cd", str) || !ft_strcmp("echo", str) ||
		!ft_strcmp("env", str) || !ft_strcmp("exit", str) ||
		!ft_strcmp("export", str) || !ft_strcmp("pwd", str) ||
		!ft_strcmp("unset", str))
		return (1);
	return (0);
}

int is_redirection(char *s)
{
	size_t length;

	length = ft_strlen(s);
	if (length == 1)
	{
        if (*s == GREAT)
			return (GREAT);
        else if (*s == LESS)
            return (LESS);
	}
    if (!ft_strcmp(s, GREATGREAT))
		return (GREAT * 2);
    else if (!ft_strcmp(s, LESSLESS))
		return (LESS * 2); 
	return (0);
}

int is_metachar(char *str)
{
	int  size;

	size = ft_strlen(str);
	if (size == 1)
	{
		if (*str == GREAT || *str == LESS || *str == PIPE)
			return (1);
	}
	if (!ft_strncmp(str, GREATGREAT, size) || !ft_strncmp(str, LESSLESS, size)) 
		return (1);
	return (0);
}

int is_special_char(int c)
{
    if (c == '?' || c == '-' || c == '@' || c == '!' || c == '*' || c == DOLLAR) 
        return (1);
    return (0);
}

int is_unclosed_quote(char *s)
{
	char quote;
	
	if (!s)
		return (0);
	while (*s) 
	{
		if (*s == QUOTE || *s == DQUOTE)
		{
			quote = *s;
			s++;
			s = ft_strchr(s, quote);
			if (!s)
				return (1);
		}
		s++;
	}
	return (0);
}

