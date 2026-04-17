/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:06:56 by omawele           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:27 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *env;

char *get_prompt_line(void)
{
    char *prompt_line;
    char *cur_dir;

    cur_dir = ft_calloc(100, sizeof(char));
    if (!cur_dir)
        return (NULL);
    if (!getcwd(cur_dir, 100))
        return (free(cur_dir), NULL);
    prompt_line = ft_strjoin(cur_dir, "# ");
    if (!prompt_line)
        return (free(cur_dir), NULL); 
    return (prompt_line);
}


void start_zansh(t_cmd *cmd)
{
    char *prompt;

    prompt = readline("zansh-0.1# ");
    if (!prompt || is_only_space(prompt))
        return;
    env = getenv("PATH");
    if (!env)
        return;
    if (parser(prompt, cmd, env))
        exit(2);
}


int main(void)
{
    t_cmd *cmd;

    cmd = cmd_init();
    if (!cmd)
        return (1);
    while (1) 
    {
        start_zansh(cmd);
        cmd_reset(cmd);
    }
    cmd_destroy(&cmd);
    return (0);  
}
