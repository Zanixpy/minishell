/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:34:39 by omawele           #+#    #+#             */
/*   Updated: 2026/05/12 18:51:12 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_cmd_output(t_cmd *cmd, char *file, int result)
{
    cmd->outfile = clean_str(file);
    if (!cmd->outfile)
        return (ERRMALLOC);
    if (result == GREAT)
    {
        if (cmd->fdout)
            close(cmd->fdout);
        cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);      
    }
    else
    {
        if (cmd->append)
            close(cmd->append);
        cmd->append = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644); 
    }
    return (0);  
}

int set_cmd_input(t_cmd *cmd, char *file)
{
    cmd->infile = clean_str(file);
    if (!cmd->infile)
        return (ERRMALLOC);
    if (cmd->fdin)
        close(cmd->fdin);
    cmd->fdin = open(cmd->infile, O_RDONLY);     
    return (0); 
}

int set_cmd_heredoc(t_cmd *cmd, char *delim)
{
    cmd->heredoc_delim = clean_str(delim);
    if (!cmd->heredoc_delim)
        return (ERRMALLOC);
    return (0);  
}



