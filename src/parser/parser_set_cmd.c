/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:04:02 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 22:42:44 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_cmd_args(t_cmd *cmd, char *token)
{
    char **tmp;

    if (cmd->args)
        tmp = add_element_in_array(cmd->args, token);
    else
        tmp = create_tab(token);
    if (!tmp)
        return (1);
    free_char_tab(&cmd->args);
    cmd->args = tmp;
	return (0);	
}

int set_cmd_and_path(t_cmd *cmd, char *token, char **envp)
{
	cmd->cmd = ft_strdup(token);
	if (!cmd->cmd)
		return (1);
	if (is_built_in_cmd(token))
	{
		cmd->path = ft_strdup("BIC");
		if (!cmd->path)
			return (free(cmd->cmd), 1);		
	}
	else
	{
		cmd->path = search_path_cmd(envp, token);
		if (!cmd->path)
			return (free(cmd->cmd), 1);
	}
	return (0);
}

int set_cmd_redirections(t_cmd *cmd, char **tokens, int pos)
{
	int fd;
    int result;

    result = is_redirection(tokens[pos]);
	if (result == GREAT)
        return 0;
	else if (result == LESS)
        return 0;
	else if (result == GREAT * 2)
        return 0;
	else if (result == LESS * 2)
        return 0;
	return (0);	
}

int set_cmd_next(t_cmd **cmd)
{
    (*cmd)->next = cmd_init();
    if (!(*cmd)->next)
        return (1);
    (*cmd) = (*cmd)->next;
    return (0);
}
