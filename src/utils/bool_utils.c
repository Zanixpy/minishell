/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:58:02 by omawele           #+#    #+#             */
/*   Updated: 2026/04/28 21:39:58 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int is_space(char *str)
{
    while (*str) 
    {
        if (*str != SPACE && (*str < 9 ||*str > 13))
            return (0);
        str++;
    }
    return (1);
}

int is_bic(char *str)
{
	if (!ft_strncmp("cd", str, 2) || !ft_strncmp("echo", str, 4) ||
		!ft_strncmp("env", str, 3) || !ft_strncmp("exit", str, 4) ||
		!ft_strncmp("export", str, 6) || !ft_strncmp("pwd", str, 3) ||
		!ft_strncmp("unset", str, 5))
		return (1);
	return (0);
}

int is_quoted(char *s)
{
	int i;
	char quote;
	
	i = 0;
    quote = 0;
	if (s[i] == QUOTE || s[i] == DQUOTE)
		quote = s[i++];
	while (s[i] && s[i++] != quote);
	if (s[i - 1] == quote)
		return (quote);
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

char *is_token(char *str)
{
	int  size;

	size = ft_strlen(str);
	if (size == 1)
	{
		if (*str == GREAT)
			return ("GREAT");
		else if (*str == LESS)
			return ("LESS");
		else if (*str == PIPE)
			return ("PIPE");
		else if (*str == DOLLAR)
			return ("DOLLAR");
	}
	if (!ft_strncmp(str, GREATGREAT, size)) 
		return ("GREATGREAT");
	else if  (!ft_strncmp(str, LESSLESS, size))
		return ("LESSLESS");
	return (NULL);
}

int is_var(char *s)
{
    int i;
    int isquoted;
    int is_dollar;
    
    isquoted = is_quoted(s);
    if (isquoted == QUOTE || isquoted == 0)
        return (0);
    i = 1;
    is_dollar = 0;
    while (s[i] != DOLLAR)
    {
        is_dollar = 1;
        i++;
    }
    if (is_dollar && (s[i] == '?' || s[i] == '-' || s[i] == '@' || s[i] == '!' || s[i] == '*'))
        return (1);
    if (is_dollar && (ft_isalnum(s[i]) || s[i] == '_'))
        return (1);
    return (0);
}

int is_special_token(int c)
{
    if (c == '?' || c == '-' || c == '@' || c == '!' || c == '*' )
        return (1);
    return (0);
}
