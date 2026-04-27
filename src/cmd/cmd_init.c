/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:44:40 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 17:24:41 by omawele          ###   ########.fr       */
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
    cmd->fdin = -2;
    cmd->fdout = -2;
    return (cmd);
}

void cmd_reset(t_cmd *cmd)
{
    cmd_destroy_data(cmd);
    cmd_destroy_node(cmd);
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->path = NULL;
    cmd->current_dir = NULL;
    cmd->fdin = -2;
    cmd->fdout = -2;
}
