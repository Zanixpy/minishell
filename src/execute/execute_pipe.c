/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:00:00 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/10 17:56:28 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_outfile_fd(t_cmd *cmd)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd->append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(cmd->outfile, flags, 0644);
	if (fd == -1)
	{
		perror(cmd->outfile);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	child_fds(t_cmd *cmd, int infd, int outfd)
{
	int	fd;

	if (infd >= 0)
		(dup2(infd, STDIN_FILENO), close(infd));
	if (outfd >= 0)
		(dup2(outfd, STDOUT_FILENO), close(outfd));
	if (cmd->fdin >= 0)
		(dup2(cmd->fdin, STDIN_FILENO), close(cmd->fdin));
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
		set_outfile_fd(cmd);
}

static void	child_run(t_cmd *cmd, int infd, int outfd, t_shell *shell)
{
	char	*path;

	child_fds(cmd, infd, outfd);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, shell));
	path = find_executable(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror(path);
	free(path);
	exit(126);
}

static pid_t	pipe_iter(t_cmd *cmd, int *prev_fd, t_shell *shell)
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
			(close(pfd[0]), close(pfd[1]));
		return (-1);
	}
	if (pid == 0)
		child_run(cmd, *prev_fd, pfd[1], shell);
	if (pfd[1] >= 0)
		close(pfd[1]);
	if (*prev_fd >= 0)
		close(*prev_fd);
	*prev_fd = pfd[0];
	return (pid);
}

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
		last_pid = pipe_iter(cur, &prev_fd, shell);
		if (last_pid == -1)
			break ;
		count++;
		cur = cur->next;
	}
	if (prev_fd >= 0)
		close(prev_fd);
	return (pipe_wait(last_pid, count));
}
