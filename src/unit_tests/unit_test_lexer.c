/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:48:22 by omawele           #+#    #+#             */
/*   Updated: 2026/04/24 16:37:35 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* THIS TEST IS USED TO SEE IF THE INPUT OF THE USER IS NICELY SEPARATE INTO TOKENS*/

void print_tab(char **tab)
{
    int i = 0;
    
    while (tab[i]) 
    {
        printf("%d, %s\n",i, tab[i]);
        i++;
    }
}

void unit_test_lexer(char *prompt)
{
    char **tokens;
    int ret;

    ret = ft_strcmp(prompt, NONE);
    if (prompt && ret)
    { 
        tokens = lexer(prompt);
        if (!tokens)
            return ;
        print_tab(tokens);
        free_char_tab(&tokens);
    }
    else if (!ret)
        ft_printf("Empty string\n");
}
