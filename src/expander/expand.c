/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 11:48:52 by omawele           #+#    #+#             */
/*   Updated: 2026/05/20 11:52:10 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static char *build_var(char *s, int *pos)
{
    char *tmp;
    int sub_len;
    
    sub_len = 0;
    if (ft_isdigit(s[*pos]) || is_special_char(s[*pos]))
    {
        sub_len++;        
        tmp = ft_substr(s, *pos, sub_len);
    }
    else 
    {
        while (ft_isalnum(s[*pos + sub_len]) || s[*pos + sub_len] == '_')
            sub_len++;
        tmp = ft_substr(s, *pos, sub_len);
    }
    if (!tmp)
        return (NULL);
    *pos += sub_len;    
    return (tmp);
}

static char *convert_var(char *s, int *pos)
{
    char *env;
    char *tmp;

    tmp = build_var(s, pos);
    if (!tmp)
        return (NULL);
    env = getenv(tmp);
    free(tmp);
    if (!env)
        tmp = ft_calloc(1, sizeof(char));
    else
        tmp = ft_strdup(env);
    if (!tmp)
        return (NULL);
    return (tmp);
}


static char *rebuild_str(char **s, int start_var, int end_var, char *var)
{
    char *tmp;
    int length;
    int i;
    int j;

    length =  ft_strlen(*s) - (end_var - start_var) + ft_strlen(var);
    tmp = ft_calloc(length + 1, sizeof(char));
    if (!tmp)
        return (free_str(s), NULL);
    i = 0;
    j = 0;
    while (i < length) 
    {
        if (j == start_var)
        {
            fill_var_in_str(&tmp, &i, var);
            j = end_var;
        }
        else
        {
            tmp[i] = (*s)[j++];
            i++;
        }
    }
    return (tmp);
}

static void format_string(char **s, int *i)
{
    char *var;
    char *tmp;
    int  end_var;

    end_var = *i + 1;
    var = convert_var(*s, &end_var);
    if (!var)
       return (free_str(s));
    tmp = rebuild_str(s, *i, end_var, var);
    free(var);
    if (!tmp)
        return (free_str(s));
    free(*s);
    *s = tmp;
}

char *expand_str(char *s)
{
    int i;

    s = strdup(s);
    if (!s)
        return (NULL);
    i = 0;
    while (s[i]) 
    {
        if (s[i] == QUOTE)
        {
            i++;
            if (ft_strchr((s + i), QUOTE))
                while (s[i] && s[i++] != QUOTE);
        }
        else if (s[i] == DOLLAR)
        {      
            format_string(&s, &i);
            if (!s)
                return (NULL);
        }
        else
            i++;
    }
    return (s);
}



/*
Caractères spéciaux qu'on peut pas expand :
/
\
'
|
(
)
<
[
]
;
=
:
{
}
~
,
.
*/

/*
Caractères spéciaux qu'on peut expand seulement eux et pas la suite:
?
-
@
!
*
*/

