/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:22:15 by omawele           #+#    #+#             */
/*   Updated: 2026/03/30 16:14:59 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

size_t count_words(char *str)
{
    size_t count;
    size_t i;
    char is_quoted;

    count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] != SPACE)
        {
            count += 1;
            if (str[i] == QUOTE || str[i] == DQUOTE)
            {
                is_quoted = str[i++];
                while (str[i] && str[i++] != is_quoted);
            }
            while (str[i] && str[i++] != SPACE);
        }
        else
            i++;
    }
    return (count); 
}

int malloc_token(char ***tokens, char *prompt, size_t *i, size_t *j)
{
    size_t length;
    size_t o;
    int is_quoted;

    length = 0;
    if (prompt[*j] == QUOTE || prompt[*j] == DQUOTE)
    {
        is_quoted = prompt[(*j)];
        while (prompt[*j + 1 + length] && prompt[*j + 1+ length++] != is_quoted);
    }
    while (prompt[*j + length] && prompt[*j + length++] != SPACE);
    (*tokens)[*i] = ft_calloc(length + 1, sizeof(char));
    if (!(*tokens)[*i])
        return (1);
    o = -1;
    while (++o < length)
        (*tokens)[*i][o] = prompt[*j + o];   
    (*i)++;
    *j += length;
    return (0);
}

int tokenization(char ***tokens, char *prompt, size_t nb_words)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (i < nb_words) 
    {
        if (prompt[j] != SPACE)
        {
            if (malloc_token(tokens, prompt, &i, &j))
                return (free_char_tab_n(tokens, i - 1), 1); 
        }
        else
            j++;
    }
    return (0); 
}


char **tokenizer(char *prompt)
{
    char **tokens;
    size_t  nb_words;
  
    tokens = NULL;
    nb_words = count_words(prompt);
    tokens = ft_calloc(nb_words + 1, sizeof(char *));
    if (!tokens)
        return (NULL);
    if (tokenization(&tokens, prompt, nb_words))
        return (NULL);
    return (tokens);    
}




