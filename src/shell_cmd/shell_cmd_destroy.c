/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:05:12 by omawele           #+#    #+#             */
/*   Updated: 2026/05/21 12:15:29 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void cmd_destroy(t_cmd **cmd)
{
    cmd_destroy_data(*cmd);
    cmd_destroy_node(*cmd);
    free(*cmd);
}

void cmd_destroy_data(t_cmd *cmd)
{
    free_str(&cmd->cmd);
    free_char_tab(&cmd->args);
    free_str(&cmd->path);
    free_str(&cmd->current_dir);
    free_str(&cmd->outfile);
    free_str(&cmd->infile);
    free_str(&cmd->heredoc_delim);
    close_fd(cmd->fdin);
    close_fd(cmd->fdout);
    close_fd(cmd->append);
}

void shell_destroy(t_shell **shell)
{
    shell_destroy_data(*shell);
    free(*shell);
}

void shell_destroy_data(t_shell *shell)
{
    if (shell->env)
        free_char_tab(&shell->env);
    if (shell->pwd)
        free(shell->pwd);
    if (shell->oldpwd)
        free(shell->oldpwd);
}

void cmd_destroy_node(t_cmd *cmd)
{
    t_cmd *cur;
    t_cmd *tmp;

    if (!cmd->next)
        return;
    cur = cmd->next;
    while (cur) 
    {
        cmd_destroy_data(cur);
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    cmd->next = NULL;
}


