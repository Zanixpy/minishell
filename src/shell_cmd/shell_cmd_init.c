/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:44:40 by omawele           #+#    #+#             */
/*   Updated: 2026/05/28 14:21:14 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *cmd_init(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    cmd->path = NULL;
    cmd->current_dir = NULL;
    cmd->args = NULL;
    cmd->next = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->heredoc_delim = NULL;
    cmd->append = -2;
    cmd->fdin = -2;
    cmd->fdout = -2;
    return (cmd);
}

t_shell *shell_init(char **envp)
{
    t_shell *shell;
    char *pwd;

    
    shell = malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    shell->exit_status = 0;
    shell->env = dup_env(envp);
    if (!shell->env)
        return (free(shell), NULL);
    pwd = NULL;
    shell->oldpwd = NULL;
    if (!getcwd(pwd, 100))
    {
        free_char_tab(&shell->env);
        free(shell);
        return (NULL);     
    }
    shell->pwd = pwd; 
    return (shell);
}

void cmd_reset(t_cmd *cmd)
{
    cmd_destroy_data(cmd);
    cmd_destroy_node(cmd);
    cmd->cmd = NULL;
    cmd->path = NULL;
    cmd->current_dir = NULL;
    cmd->args = NULL;
    cmd->next = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->heredoc_delim = NULL;
    cmd->append = -2;
    cmd->fdin = -2;
    cmd->fdout = -2;
}


