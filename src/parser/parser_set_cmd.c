/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:04:02 by omawele           #+#    #+#             */
/*   Updated: 2026/05/21 16:13:37 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_cmd_args(t_cmd *cmd, char *token)
{
    char **tmp;
    char *clean_token;

    clean_token = clean_str(token, 0);
    if (!clean_token)
        return (ERRMALLOC);
    tmp = add_element_in_array(cmd->args, clean_token);
    free(clean_token);
    if (!tmp)
        return (ERRMALLOC);
    free_char_tab(&cmd->args);
    cmd->args = tmp;
	return (0);	
}
 
int set_cmd_and_path(t_cmd *cmd, char *token, char **envp)
{
    free_str(&cmd->cmd);
    free_str(&cmd->path);
    free_char_tab(&cmd->args);
	cmd->cmd = clean_str(token, 0);
    if (!cmd->cmd)
		return (1);
    if (is_bic(token))
		cmd->path = ft_strdup(cmd->cmd);
    else if (*cmd->cmd == '\0')
        cmd->path = ft_calloc(1, sizeof(char));
    else
		cmd->path = search_path_cmd(envp, cmd->cmd);
    if (!cmd->path)
        return (free(cmd->cmd), 1);
    cmd->args = create_tab(cmd->path);
    if (!cmd->args)
        return (free(cmd->cmd), free(cmd->path), 1);
    return (0);
}

int set_cmd_redirections(t_cmd *cmd, char **tokens, int *pos)
{
    int result;
    int ret;

    result = is_redirection(tokens[*pos]);
    if (!tokens[*pos + 1])
        return (2);
    *pos += 1;
	if (result == GREAT || result == GREAT * 2)
        ret = set_cmd_output(cmd, tokens[*pos], result);
	if (result == LESS)
        ret = set_cmd_input(cmd, tokens[*pos]);
	else if (result == LESS * 2)
        ret = set_cmd_heredoc(cmd, tokens[*pos]);
	return (ret);	
}

int set_cmd_next(t_cmd **cmd)
{
    (*cmd)->next = cmd_init();
    if (!(*cmd)->next)
        return (1);
    return (0);
}
