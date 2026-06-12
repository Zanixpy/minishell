/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:00:00 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/12 11:42:31 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* set_outfile_fd:
 *	Applies the output redirection for a child process.
 *	Prefers the pre-opened fd from the parser (cmd->append for >>,
 *	cmd->fdout for >). Falls back to opening cmd->outfile only when
 *	neither pre-opened fd is valid. Uses >= 0 so the -2 sentinel
 *	never triggers a dup2/close.
 */
static void	set_outfile_fd(t_cmd *cmd)
{
	int	fd;

	if (cmd->append >= 0)
	{
		dup2(cmd->append, STDOUT_FILENO);
		close(cmd->append);
		return ;
	}
	if (cmd->fdout >= 0)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
		return ;
	}
	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("mcsh: ", STDERR_FILENO);
		perror(cmd->outfile);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/* child_fds:
 *	Sets up input and output file descriptors for a child process.
 *	Applies pipe connections, heredoc input, and file redirections
 *	before command execution.
 */
static void	child_fds(t_cmd *cmd, int infd, int outfd)
{
	int	fd;

	dup_fd(infd, STDIN_FILENO);
	dup_fd(outfd, STDOUT_FILENO);
	if (cmd->fdin >= 0)
	{
		dup_fd(cmd->fdin, STDIN_FILENO);
		cmd->fdin = -1;
	}
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			exit(1);
		}
		dup_fd(fd, STDIN_FILENO);
	}
	if (cmd->outfile)
		set_outfile_fd(cmd);
}

/* child_run:
 *	Executes a command inside a child process.
 *	Sets up file descriptors, executes builtin commands directly,
 *	or runs external commands using execve.
 *	Calls child_cleanup_exit before every exit so valgrind sees no leaks.
 */
static void	child_run(t_cmd *cmd, int infd, int outfd, t_shell *shell,
		t_cmd *head)
{
	char	*path;
	int		status;

	reset_signals_for_child();
	child_fds(cmd, infd, outfd);
	if (!cmd->args || !cmd->args[0])
		child_cleanup_exit(head, shell, 0);
	if (is_bic(cmd->args[0]))
	{
		status = execute_builtin(cmd, shell);
		child_cleanup_exit(head, shell, status);
	}
	path = find_executable(cmd->args[0], shell->env);
	if (!path)
	{
		err_cmd_not_found(cmd->args[0]);
		child_cleanup_exit(head, shell, 127);
	}
	execve(path, cmd->args, shell->env);
	perror(path);
	free(path);
	child_cleanup_exit(head, shell, 126);
}

/* pipe_iter:
 *	Creates a pipe and forks a child process for one command
 *	in the pipeline.
 *	Updates the previous pipe read end for the next command.
 *	Returns the child process pid or -1 on error.
 */
static pid_t	pipe_iter(t_cmd *cmd, int *prev_fd, t_shell *shell, t_cmd *head)
{
	int		pfd[2];
	pid_t	pid;

	pfd[0] = -1;
	pfd[1] = -1;
	if (cmd->next && pipe(pfd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		if (pfd[0] >= 0)
			close_pipe(pfd[0], pfd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close_fd(pfd[0]);
		child_run(cmd, *prev_fd, pfd[1], shell, head);
	}
	close_fd(pfd[1]);
	close_fd(*prev_fd);
	*prev_fd = pfd[0];
	return (pid);
}

/* execute_pipe:
 *	Executes multiple commands connected by pipes.
 *	Creates child processes for each command and waits for all
 *	processes to finish execution.
 *	Returns the exit status of the last command in the pipeline.
 */
int	execute_pipe(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;
	int		prev_fd;
	pid_t	last_pid;
	int		count;

	if (!cmds)
		return (0);
	prev_fd = -1;
	count = 0;
	cur = cmds;
	last_pid = 0;
	while (cur)
	{
		last_pid = pipe_iter(cur, &prev_fd, shell, cmds);
		if (last_pid == -1)
			break ;
		count++;
		cur = cur->next;
	}
	if (prev_fd >= 0)
		close(prev_fd);
	ignore_signals_in_parent();
	count = pipe_wait(last_pid, count);
	setup_signals();
	return (count);
}
