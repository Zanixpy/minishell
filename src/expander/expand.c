/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 11:48:52 by omawele           #+#    #+#             */
/*   Updated: 2026/04/28 20:16:29 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *convert_var(char *s, int *pos)
{
    int sub_len;
    char *env;
    char *tmp;

    sub_len = 0;
    if (ft_isdigit(s[*pos]) || is_special_token(s[*pos]))
        tmp = ft_substr(s, *pos, 1);
    else 
    {
        while (ft_isalnum(s[*pos + sub_len]) || s[*pos + sub_len] == '_')
            sub_len++;
        tmp = ft_substr(s, 1, sub_len);
    }
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
    *pos += sub_len;
    return (tmp);
}

static int adjust_buffer(char **buffer, int *pos)
{
    int i;
    char *tmp_buf;
    char *tmp;

    i = *pos;
    tmp = convert_var(*buffer, pos);
    if (!tmp)
    {
        free_str(buffer);
        *buffer = NULL;
        return (1);   
    }
    if (i == 0)
        *buffer = ft_strjoin("", tmp);
    else
    {
        tmp_buf = *buffer;
        *buffer = ft_strjoin(tmp_buf, tmp);
        free(tmp_buf);    
    }
    free(tmp);
    if (!(*buffer))
        return (1);
    return (0);
}

char *expand_var(char *s)
{
    char *buffer;
    int i;

    s = extract_in_quote(s);
    if (!s)
        return (NULL);
    i = 0;
    while (s[i]) 
    {
        if (s[i] == DOLLAR)
        {
            i++;
            if (adjust_buffer(&buffer, &i))
                return (free(s), NULL);
        }
        i++;
    }
    free(s);
    return (buffer);
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

