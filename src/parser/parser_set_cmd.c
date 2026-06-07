/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:04:02 by omawele           #+#    #+#             */
/*   Updated: 2026/06/07 21:55:35 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_cmd_args(t_cmd *cmd, t_shell *shell, char *token)
{
	char	**tmp;
	char	*clean_token;

	clean_token = clean_str(token, 0, shell->exit_status);
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

int	set_cmd_and_path(t_cmd *cmd, t_shell *shell, char *token)
{
	char	**path_env;

	path_env = get_path_split();
	if (!path_env)
		return (ERRMALLOC);
	cmd->cmd = clean_str(token, 0, shell->exit_status);
	if (!cmd->cmd)
		return (free_char_tab(&path_env), ERRMALLOC);
	if (is_bic(token) || cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && 
		(cmd->cmd[1] == '/' || (cmd->cmd[1] == '.'&& cmd->cmd[2] == '/'))))
		cmd->path = ft_strdup(cmd->cmd);
	else if (*cmd->cmd == '\0')
		cmd->path = ft_calloc(1, sizeof(char));
	else if (path_env)
		cmd->path = search_path_cmd(path_env, cmd->cmd);
	else
		cmd->path = ft_strdup(cmd->cmd);
	free_char_tab(&path_env);
	if (!cmd->path)
		return (free(cmd->cmd), ERRMALLOC);
	cmd->args = create_tab(cmd->path);
	if (!cmd->args)
		return (free(cmd->cmd), free(cmd->path), ERRMALLOC);
	return (0);
}

int	set_cmd_redirections(t_cmd *cmd, t_shell *shell, char **tokens, int *pos)
{
	int	result;
	int	ret;

	result = is_redirection(tokens[*pos]);
	if (!tokens[*pos + 1])
		return (perror_syntax(0, cmd, shell));
	*pos += 1;
	if (result == GREAT || result == GREAT * 2)
		ret = set_cmd_output(cmd, shell, tokens[*pos], result);
	if (result == LESS)
		ret = set_cmd_input(cmd, shell, tokens[*pos]);
	else if (result == LESS * 2)
		ret = set_cmd_heredoc(cmd, shell, tokens[*pos]);
	return (ret);
}

int	set_cmd_next(t_cmd **cmd, t_shell *shell, char *token, int pos)
{
	if (!token || is_metachar(token) || pos == 0)
		return (perror_syntax(1, *cmd, shell));
	(*cmd)->next = cmd_init();
	if (!(*cmd)->next)
		return (ERRMALLOC);
	return (0);
}
