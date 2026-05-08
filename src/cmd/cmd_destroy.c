/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:05:12 by omawele           #+#    #+#             */
/*   Updated: 2026/05/08 19:45:33 by omawele          ###   ########.fr       */
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
    if (cmd->cmd)
        free(cmd->cmd);
    if (cmd->args)
        free_char_tab(&cmd->args);
    if (cmd->path)
        free(cmd->path);
    if (cmd->current_dir)
        free(cmd->current_dir);
    if (cmd->fdin > 2)
        close(cmd->fdin);
    if (cmd->fdout > 2)
        close(cmd->fdout);
    cmd->fdin = -2;
    cmd->fdout = -2;
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


