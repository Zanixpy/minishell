/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:11:49 by omawele           #+#    #+#             */
/*   Updated: 2026/05/29 10:52:15 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int perror_redir_io(int code, t_cmd *cmd, t_shell *shell)
{  
    if (code)
    {
        if (cmd->fdin == -1)
        {
            shell->exit_status = ERRSYNTAX;
            ft_putstr_fd("mcsh: ", STDERR_FILENO);
            if (*cmd->infile == '\0')
                ft_putstr_fd(": ", STDERR_FILENO);         
            return (perror(cmd->infile), 1);
        }            
    }
    else
    {
        if (cmd->fdout == -1 || cmd->append == -1)
        {
            shell->exit_status = ERRSYNTAX;
            ft_putstr_fd("mcsh: ", STDERR_FILENO);
            if (*cmd->outfile == '\0')
                ft_putstr_fd(": ", STDERR_FILENO);     
            return (perror(cmd->outfile), 1);
        }   
    }
    return (0);
}

int perror_redir_meta(char *token, t_shell *shell)
{  
    if (!ft_strcmp("<", token))
        ft_putstr_fd("mcsh: syntax error near unexpected token `<'\n", STDERR_FILENO);
    else if (!ft_strcmp(">", token))
        ft_putstr_fd("mcsh: syntax error near unexpected token `>'\n", STDERR_FILENO);
    else if (!ft_strcmp("|", token))
        ft_putstr_fd("mcsh: syntax error near unexpected token `|'\n", STDERR_FILENO);
    else if (!ft_strcmp(">>", token))
        ft_putstr_fd("mcsh: syntax error near unexpected token `>>'\n", STDERR_FILENO);
    else if (!ft_strcmp("<<", token))
        ft_putstr_fd("mcsh: syntax error near unexpected token `<<'\n", STDERR_FILENO);
    shell->exit_status = ERRSYNTAX;
    return (1);
}

int perror_syntax(int code, t_cmd *cmd, t_shell *shell)
{
    if (code == 0)
    {
        ft_putstr_fd("mcsh: syntax error near unexpected token `newline'\n", STDERR_FILENO);
        delete_file(cmd);
        
    }
    else if (code == 1)
        ft_putstr_fd("mcsh: syntax error near unexpected token `|'\n", STDERR_FILENO);
    else if (code == 2)
        ft_putstr_fd("mcsh: syntax error: unclosed quotes\n", STDERR_FILENO);
    shell->exit_status = ERRSYNTAX;
    return (1);
}

