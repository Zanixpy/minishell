/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:44:40 by omawele           #+#    #+#             */
/*   Updated: 2026/06/03 23:35:23 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->current_dir = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_quoted = 0;
	cmd->append = -2;
	cmd->fdin = -2;
	cmd->fdout = -2;
	return (cmd);
}

t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->exit_status = 0;
	shell->input = NULL;
	shell->env = dup_env(envp);
	if (!shell->env)
		return (free(shell), NULL);
	shell->oldpwd = NULL;
	shell->pwd = getcwd(NULL, 0);
	if (!shell->pwd)
	{
		free_char_tab(&shell->env);
		free(shell);
		return (NULL);
	}
	return (shell);
}

void	cmd_reset(t_cmd *cmd)
{
	cmd_destroy_data(cmd);
	cmd_destroy_node(cmd);
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->current_dir = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_quoted = 0;
	cmd->append = -2;
	cmd->fdin = -2;
	cmd->fdout = -2;
}
