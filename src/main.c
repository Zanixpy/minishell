/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:06:56 by omawele           #+#    #+#             */
/*   Updated: 2026/04/28 22:05:33 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char *env;

void print_tab(char **args)
{
    int i;

    i = 0;
    while (args[i]) 
    {
        printf("args[%d] : %s\n", i, args[i]);
        i++;
    }
    if (!args[i])
        printf("args[%d] : NULL\n", i);
}

void print_cmd(t_cmd *cmd)
{
    int i = 0;
    
    while (cmd) 
    {
        printf("============= NODE %d ==================\n", i);
        if (cmd->cmd)
            printf("cmd : %s\n", cmd->cmd);
        if (cmd->args)
            print_tab(cmd->args);
        if (cmd->path)
            printf("cmd path : %s\n", cmd->path);
        if (cmd->current_dir)
            printf("current_dir : %s\n", cmd->path);
        printf("fdin : %d\n", cmd->fdin);
        printf("fdout : %d\n", cmd->fdout);
        printf("========================================\n");
        cmd = cmd->next;
        i++;
    }
}

int get_prompt_line(t_cmd *cmd)
{
    char *prompt;
    
    prompt = readline("mshell-0.2# ");
    if (!prompt || is_space(prompt))
        return (free(prompt), 0);
    env = getenv("PATH");
    if (!env)
        return (free(prompt), 1);
    if (parser(prompt, cmd, env))
        return (free(prompt),1);
    print_cmd(cmd);
    free(prompt);
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
        cmd_reset(cmd);
    }
    cmd_destroy(&cmd);
    return (0);  
}
