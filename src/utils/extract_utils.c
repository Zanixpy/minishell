/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:05:10 by omawele           #+#    #+#             */
/*   Updated: 2026/05/04 00:41:00 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <cstddef>
#include <string.h>

static int is_valid_quote(char *s, char quote, int i)
{
    int j;

    if (s[i] == '\0')
        return (-1);
    j = 0;
    while (s[i + j] && s[i + j] != quote)
        j++;
    if (s[i + j] == quote)
        return (j);
    return (0);
}

int extract_str_in_quote(char *s, char **buffer, char c, int *i)
{
    char *tmp;
    int j;
    int ret;

    j = *i + 1;;
    ret = is_valid_quote(s, s[j], j);
    tmp = NULL;
    if (ret)
    {
        tmp = ft_substr(s, j, ret);
        if (!tmp)
            return (1);   
    } 
    *i += ret;
    return (0);
}

char *extract_str(char *s)
{
    int i;
    char *tmp;
    char *buffer;
    char *final;

    i = 0;
    while (s[i]) 
    {
        if (s[i] == QUOTE || s[i] == DQUOTE)
        {
            if (extract_str_in_quote(s, &buffer, s[i], &i))
        }
    
    }
}


char *clean_str(char *s)
{
    char *tmp;
	
	if (is_there_quote(s))
		tmp = extract_str(s);
	else
	 	tmp = ft_strdup(s);
	if (!tmp)
		return (NULL);
	return (tmp);
}
