/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:18:48 by omawele           #+#    #+#             */
/*   Updated: 2026/04/24 19:08:13 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int ft_isspace(char *str)
{
    while (*str) 
    {
        if (*str != SPACE && (*str < 9 ||*str > 13))
            return (0);
        str++;
    }
    return (1);
}

int is_built_in_cmd(char *str)
{
	if (!ft_strncmp("cd", str, 2) || !ft_strncmp("echo", str, 4) ||
		!ft_strncmp("env", str, 3) || !ft_strncmp("exit", str, 4) ||
		!ft_strncmp("export", str, 6) || !ft_strncmp("pwd", str, 3) ||
		!ft_strncmp("unset", str, 5))
		return (0);
	return (1);
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

int is_quoted(char *s)
{
	int i;
	char quote;
	
	i = 0;
	if (s[i] == QUOTE || s[i] == DQUOTE)
		quote = s[i++];
	while (s[i] && s[i++] != quote);
	if (s[i - 1] == quote)
		return (1);
	return (0);
}

int ft_strcmp(const char *s1, const char *s2)
{
	int n;

	n = 0;
	while (s1[n] || s2[n]) 
	{
		if (s1[n] != s2[n])
			return 1;
		n++;
	}
	return 0;
}


char *extract_inside_quote(char *s)
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
