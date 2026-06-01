/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:26:02 by omawele           #+#    #+#             */
/*   Updated: 2026/05/29 10:47:03 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void close_fd(int fd)
{
    if (fd >= 0)
        close(fd);
}

void delete_file(t_cmd *cmd)
{
    if (cmd->outfile && (cmd->fdout || cmd->append))
    {
        
        close_fd(cmd->fdout);
        close_fd(cmd->append);
        unlink(cmd->outfile);
    }
}