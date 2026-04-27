/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:06:56 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 22:26:18 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdlib.h>

char *env;

int get_prompt_line(t_cmd *cmd)
{
    (void)cmd;
    char *prompt;
    

    prompt = readline("mshell-0.2# ");
    if (!prompt)
        return (1);
    else if (is_space(prompt))
        return (1);
    env = getenv("PATH");
    if (!env)
        return 1;
    // unit_test_lexer(prompt);
    if (parser(prompt, cmd, env))
        return 1;
    return (0);
}

/* MAIN : This is the beginning of the program where we'll launch the shell with the infinite loop*/

int main(void)
{
    t_cmd *cmd;

    cmd = cmd_init();
    if (!cmd)
        return (1);
    while (1) 
    {
        if (get_prompt_line(cmd))
            break; 
    }
    cmd_destroy(&cmd);
    return (0);  
}
