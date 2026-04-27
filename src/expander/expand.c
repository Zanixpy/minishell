/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 11:48:52 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 17:23:46 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *extract_var(char *s)
{
	char *tmp;
	int len;
	int i;

	len = strlen(s) - 3;
	tmp = calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len) 
	{
		tmp[i] = s[i + 2];
		i++;
	}
	return (tmp);	
}

char *expand_var(char *s)
{
    char *env;
    char *tmp;
    char *final;

    tmp = extract_var(s);
    if (!tmp)
        return NULL;
    env = getenv(tmp);
    free(tmp);
    tmp = NULL;

    return (tmp);
}

int is_var(char *s)
{
    int i;
    int isquoted;
    
    isquoted = is_quoted(s);
    if (isquoted == QUOTE || isquoted == 0 || s[1] != DOLLAR)
        return (0);    
    i = 2;
    while (s[i])
    {
        if(!ft_isprint(s[i]))
            return (0);
        i++;
    }
    return (1);
}



