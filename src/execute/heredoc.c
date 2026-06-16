/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 20:32:46 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/16 20:32:51 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* heredoc_write_line:
 *	Writes one heredoc line to the pipe, expanding variables unless the
 *	delimiter was quoted.  Returns 1 on expansion error and 0 otherwise.
 */
static int	heredoc_write_line(char *line, int fd, t_shell *shell, int quoted)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_str(line, shell->exit_status, shell->env);
		if (!expanded)
			return (1);
		ft_putstr_fd(expanded, fd);
		write(fd, "\n", 1);
		free(expanded);
	}
	else
	{
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
	}
	return (0);
}

/* heredoc_child:
 *	Runs in the forked child with the default SIGINT behaviour so that
 *	Ctrl-C aborts the here-document immediately.  Reads lines until the
 *	delimiter or EOF, writes them to the pipe, then exits.
 */
static void	heredoc_child(int *fds, char **delim, t_shell *shell, int quoted)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fds[0]);
	while (1)
	{
		line = readline("> ");
		if (handle_heredoc_cond(&line, *delim))
			break ;
		if (heredoc_write_line(line, fds[1], shell, quoted))
		{
			free(line);
			close(fds[1]);
			exit(1);
		}
		free(line);
	}
	close(fds[1]);
	exit(0);
}

/* heredoc_status:
 *	Interprets the child's wait status.  On SIGINT it flags g_signal,
 *	sets exit status 130 and returns -1 to abort.  On any non-zero exit
 *	it also aborts.  Otherwise the pipe read end becomes the stdin fd.
 */
static int	heredoc_status(int status, int read_fd, t_shell *shell)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		shell->exit_status = 130;
		g_signal = SIGINT;
		return (close(read_fd), -1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (close(read_fd), -1);
	return (read_fd);
}

/* handle_heredoc:
 *	Reads a here-document in a child process so SIGINT can interrupt it.
 *	The parent ignores SIGINT while waiting, then restores its handlers.
 *	Returns the pipe read end as the command's stdin, or -1 on abort.
 */
int	handle_heredoc(char **delim, t_shell *shell, int quoted)
{
	int		fds[2];
	pid_t	pid;
	int		status;

	if (!delim || !*delim || !**delim)
		return (-1);
	if (pipe(fds) == -1)
		return (-1);
	ignore_signals_in_parent();
	pid = fork();
	if (pid == -1)
		return (close_pipe(fds[1], fds[0]), setup_signals(), -1);
	if (pid == 0)
		heredoc_child(fds, delim, shell, quoted);
	close(fds[1]);
	waitpid(pid, &status, 0);
	setup_signals();
	return (heredoc_status(status, fds[0], shell));
}

/* setup_heredoc:
 *	Reads ALL heredoc delimiters in order (left to right), as bash does.
 *	Each heredoc is fully consumed; only the last one's fd becomes stdin.
 *	Returns 0 on success and 1 on error or interrupt.
 */
int	setup_heredoc(t_cmd *cmd, t_shell *shell)
{
	int	fd;
	int	i;

	if (!cmd->heredoc_delim || !cmd->heredoc_delim[0])
		return (0);
	i = 0;
	while (cmd->heredoc_delim[i])
	{
		fd = handle_heredoc(&cmd->heredoc_delim[i], shell, cmd->heredoc_quoted);
		if (fd == -1)
			return (1);
		close_fd(cmd->fdin);
		cmd->fdin = fd;
		i++;
	}
	return (0);
}
