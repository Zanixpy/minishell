/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:10 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/04 00:51:11 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	apply_infile(t_command *cmd)
{
	int	fd;

	if (cmd->input_fd != -1)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	if (!cmd->infile)
		return (0);
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->infile);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	apply_outfile(t_command *cmd)
{
	int	flags;
	int	fd;

	if (cmd->output_fd != -1)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
	if (!cmd->outfile)
		return (0);
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd->append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(cmd->outfile, flags, 0644);
	if (fd == -1)
	{
		perror(cmd->outfile);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	reset_redirections(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

int	execute_single_command(t_command *cmd, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (setup_heredoc(cmd, shell))
		return (reset_redirections(stdin_backup, stdout_backup), 1);
	if (apply_infile(cmd) || apply_outfile(cmd))
		return (reset_redirections(stdin_backup, stdout_backup), 1);
	if (is_builtin(cmd->args[0]))
		status = execute_builtin(cmd, shell);
	else
		status = execute_external(cmd, shell);
	reset_redirections(stdin_backup, stdout_backup);
	return (status);
}
