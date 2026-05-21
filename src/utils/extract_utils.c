/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:05:10 by omawele           #+#    #+#             */
/*   Updated: 2026/05/21 10:51:58 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void rebuild_str(char **s, int start_quote, int end_quote)
{
    char *tmp;
    int length;
    int i;
    int j;

    length = ft_strlen(*s) - 2;
    tmp = ft_calloc(length + 1, sizeof(char));
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

    s = ft_strdup(s);
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

static char* strremove_closed_quotes(char *s)
{
    char *tmp;
    int length;

    length = ft_strlen(s);
    if (length - 2 == 0)
        tmp = ft_calloc(1, sizeof(char));
    else        
        tmp = ft_substr(s, 1, length - 2);
    if (!tmp)
        return (NULL);
    return (tmp);
}

void fill_var_in_str(char **tmp, int *i, char *var)
{    
    if (*var == 0)
        return ;
    while (*var) 
    {
        (*tmp)[*i] = *var;
        *i += 1;
        var++;
    }
}

char *clean_str(char *s, int is_delim)
{
    char *tmp;
    char *temp_str;
    
    if (is_delim)
        temp_str = ft_strdup(s);
    else
        temp_str = expand_str(s);
    if (!temp_str)
        return (NULL);
    if (*temp_str == '\0')
        return (temp_str);
    if (is_quoted(temp_str))
        tmp = strremove_closed_quotes(temp_str);
    else if (ft_strchr(temp_str, QUOTE) || ft_strchr(temp_str, DQUOTE))
        tmp = strremove_quotes(temp_str);
    else
        tmp = ft_strdup(temp_str);
    free(temp_str);
    if (!tmp)
        return (NULL);
    return (tmp);        
}
