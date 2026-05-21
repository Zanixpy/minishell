/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:58:02 by omawele           #+#    #+#             */
/*   Updated: 2026/05/21 09:53:22 by omawele          ###   ########.fr       */
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

// char *is_token(char *str)
// {
// 	int  size;

// 	size = ft_strlen(str);
// 	if (size == 1)
// 	{
// 		if (*str == GREAT)
// 			return ("GREAT");
// 		else if (*str == LESS)
// 			return ("LESS");
// 		else if (*str == PIPE)
// 			return ("PIPE");
// 		else if (*str == DOLLAR)
// 			return ("DOLLAR");
// 	}
// 	if (!ft_strncmp(str, GREATGREAT, size)) 
// 		return ("GREATGREAT");
// 	else if  (!ft_strncmp(str, LESSLESS, size))
// 		return ("LESSLESS");
// 	return (NULL);
// }

int is_quoted(char *s)
{
    char quote;
    int i;
    
    i = 0;
    if (s[i] == QUOTE || s[i] == DQUOTE)
        quote = s[i++];
    else
        return (0);
    while (s[i] && s[i] != quote)
        i++;
    if (s[i] == quote && s[i + 1] == '\0')
        return (1);
    return (0);   
}

int is_special_char(int c)
{
    if (c == '?' || c == '-' || c == '@' || c == '!' || c == '*' || c == DOLLAR) 
        return (1);
    return (0);
}
