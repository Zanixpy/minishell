/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:05:10 by omawele           #+#    #+#             */
/*   Updated: 2026/05/08 12:04:19 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void rebuild_str(char **s, int start_quote, int end_quote)
{
    char *tmp;
    int length;
    int i;
    int j;

    length = strlen(*s) - 2;
    tmp = calloc(length + 1, sizeof(char));
    if (!tmp)
    {
        free(*s);
        *s = NULL;
        return;
    }
    i = 0;
    j = 0;
    while (i < length) 
    {
        if (j == start_quote || j == end_quote)
            j++;
        tmp[i] = (*s)[j];
        i++;
        j++;
    }
    free(*s);
    *s = tmp;
}

static char *strremove_quotes(char *s)
{
    char quote;
    int i;
    int j;

    s = strdup(s);
    if (!s)
        return (NULL);
    i = -1;
    while (s[++i]) 
    {
        if ((s[i] == QUOTE || s[i] == DQUOTE))
        {
            quote = s[i];
            j = i + 1;
            while (s[j] && s[j++] != quote);
            if (s[--j] == quote && s[j + 1])
            {
                rebuild_str(&s, i, j);
                if (!s)
                    return (NULL);
                i = j - 2;
            }
        }
    }
    return (s);
}


char *clean_str(char *s)
{
    char *tmp;
    
    if (ft_strchr(s, QUOTE) || ft_strchr(s, DQUOTE))
        tmp = strremove_quotes(s);
    else
        tmp = ft_strdup(s);
    if (!tmp)
        return (NULL);
    return (tmp);        
}
