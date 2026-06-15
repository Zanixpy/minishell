/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:10 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/12 18:02:02 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* apply_infile:
 *	Applies the input redirection for a command.
 *	Uses fdin if it already exists, otherwise opens the infile
 *	and redirects it to standard input.
 *	Returns 0 on success and 1 on error.
 */
static int	apply_infile(t_cmd *cmd)
{
	int	fd;

	if (cmd->fdin >= 0)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
		cmd->fdin = -2;
	}
	if (!cmd->infile)
		return (0);
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		err_default(cmd->infile);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/* apply_outfile:
 *	Applies the output redirection for a command.
 *	cmd->append and cmd->fdout hold pre-opened fds from the parser
 *	(append = fd for >>, fdout = fd for >). Both are checked with
 *	>= 0 so that the -2 sentinel never triggers a dup2/close.
 *	Returns 0 on success and 1 on error.
 */
static int	apply_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd->append >= 0)
	{
		dup_fd(cmd->append, STDOUT_FILENO);
		cmd->append = -2;
		return (0);
	}
	if (cmd->fdout >= 0)
	{
		dup_fd(cmd->fdout, STDOUT_FILENO);
		cmd->fdout = -2;
		return (0);
	}
	if (!cmd->outfile)
		return (0);
	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		err_default(cmd->outfile);
		return (1);
	}
	dup_fd(fd, STDOUT_FILENO);
	return (0);
}

/* reset_redirections:
 *	Restores the original standard input and output file descriptors.
 *	Closes the backup descriptors after restoring them.
 */
void	reset_redirections(int *stdin_backup, int *stdout_backup)
{
	if (*stdin_backup != -1)
	{
		dup2(*stdin_backup, STDIN_FILENO);
		close(*stdin_backup);
		*stdin_backup = -1;
	}
	if (*stdout_backup != -1)
	{
		dup2(*stdout_backup, STDOUT_FILENO);
		close(*stdout_backup);
		*stdout_backup = -1;
	}
}

/* execute_single_command:
 *	Executes a single command without creating a pipeline.
 *	Applies file redirections before execution (heredoc is set up
 *	by the caller via setup_all_heredocs before this is called).
 *	Executes builtins in the main process and external commands
 *	in a child process.
 *	Restores the original standard input and output afterward.
 *	Returns the command exit status.
 */
static int	has_redirection(t_cmd *cmd)
{
	if (cmd->fdin >= 0 || cmd->infile || cmd->fdout >= 0 || cmd->append >= 0
		|| cmd->outfile)
		return (1);
	return (0);
}

int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	if (!cmd || !cmd->args)
		return (0);
	stdin_backup = -1;
	stdout_backup = -1;
	if (has_redirection(cmd))
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
	}
	if (apply_infile(cmd) || apply_outfile(cmd))
		return (reset_redirections(&stdin_backup, &stdout_backup), 1);
	if (is_bic(cmd->args[0]))
	{
		if (ft_strcmp(cmd->args[0], "exit") == 0)
			reset_redirections(&stdin_backup, &stdout_backup);
		status = execute_builtin(cmd, shell);
	}
	else
		status = execute_external(cmd, shell, stdin_backup, stdout_backup);
	reset_redirections(&stdin_backup, &stdout_backup);
	return (status);
}
