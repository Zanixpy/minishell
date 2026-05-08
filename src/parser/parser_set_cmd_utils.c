/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:34:39 by omawele           #+#    #+#             */
/*   Updated: 2026/05/08 20:49:07 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int set_cmd_outfile(t_cmd *cmd, char *file, int result)
{
    cmd->outfile = ft_strdup(file);
    if (!cmd->outfile)
        return (1);
    if (cmd->fdout)
        close(cmd->fdout);
    if (result == GREAT)
        cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);   
}

int set_cmd_infile();
