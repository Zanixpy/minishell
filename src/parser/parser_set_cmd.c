/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:04:02 by omawele           #+#    #+#             */
/*   Updated: 2026/05/08 20:39:33 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_cmd_args(t_cmd *cmd, char *token)
{
    char **tmp;
    char **tmp_tab;

    if (cmd->args)
        tmp = add_element_in_array(cmd->args, token);
    else
    {
        tmp_tab = create_tab(cmd->path);
        if (!tmp_tab)
            return (1);
        tmp = add_element_in_array(tmp_tab, token);
        free_char_tab(&tmp_tab);
    }   
    if (!tmp)
        return (1);
    free_char_tab(&cmd->args);
    cmd->args = tmp;
	return (0);	
}
 
int set_cmd_and_path(t_cmd *cmd, char *token, char **envp)
{
	cmd->cmd = clean_str(token);
	if (!cmd->cmd)
		return (1);
	if (is_bic(token))
	{
		cmd->path = ft_strdup("BIC");
		if (!cmd->path)
			return (free(cmd->cmd), 1);		
	}
	else
	{
		cmd->path = search_path_cmd(envp, cmd->cmd);
		if (!cmd->path)
			return (free(cmd->cmd), 1);
	}
	return (0);
}

int set_cmd_redirections(t_cmd *cmd, char **tokens, int *pos)
{
    int result;

    result = is_redirection(tokens[*pos]);
    if (!tokens[*pos + 1])
        return (1);
    *pos += 1;
	if (result == GREAT || result == GREAT * 2)
    {
        cmd->outfile = tokens[*pos];

    }
	if (result == LESS)
    {
        cmd->infile = ft_strdup(tokens[*pos]);
        if (cmd->fdin)
            close(cmd->fdin);
        cmd->fdin = open(tokens[*pos], O_RDONLY);
    }
	else if (result == LESS * 2)
    {
        cmd->heredoc_quoted = 1;
        cmd->heredoc_delim = tokens[*pos];       
    }
    if (cmd->fdin == -1 || cmd ->fdout == -1)
    return (close_fds(cmd->fdin, cmd->fdout), 1);
	return (0);	
}

int set_cmd_next(t_cmd **cmd)
{
    (*cmd)->next = cmd_init();
    if (!(*cmd)->next)
        return (1);
    return (0);
}
