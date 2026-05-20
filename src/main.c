/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:06:56 by omawele           #+#    #+#             */
/*   Updated: 2026/05/20 16:07:15 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
            printf("current_dir : %s\n", cmd->current_dir);
        if (cmd->outfile)
            printf("outfile : %s\n", cmd->outfile);
        if (cmd->infile)
            printf("infile : %s\n", cmd->infile);
        if (cmd->heredoc_delim)
            printf("heredoc_delim : %s\n", cmd->heredoc_delim);
        printf("append : %d\n", cmd->append);
        printf("fdin : %d\n", cmd->fdin);
        printf("fdout : %d\n", cmd->fdout);
        printf("========================================\n");
        cmd = cmd->next;
        i++;
    }
}

int get_prompt_line(t_cmd *cmd, t_shell *shell)
{
    char *prompt;
    
    prompt = readline("mshell-0.2# ");
    if (!prompt || is_space(prompt))
        return (free(prompt), 0);
    env = getenv("PATH");
    if (!env)
        return (free(prompt), 1);
    if (parser(prompt, cmd, env))
        return (free(prompt), 1);
    print_cmd(cmd);
    shell->exit_status = execute_commands(cmd, shell);
    free(prompt);
    return (0);
}


/* MAIN : This is the beginning of the program where we'll launch the shell with the infinite loop*/

int main(int ac, char **av, char**envp)
{
    t_cmd *cmd;
    t_shell *shell;

    (void)ac;
    (void)av;
    cmd = cmd_init();
    if (!cmd)
        return (1);
    shell = shell_init(envp);
    if (!shell)
        return (cmd_destroy(&cmd), 1);
    while (1) 
    {
        if (get_prompt_line(cmd, shell))
            break;
        cmd_reset(cmd);
    }
    cmd_destroy(&cmd);
    shell_destroy(&shell);
    return (0);  
}
