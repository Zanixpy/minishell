/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:13 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/01 14:03:31 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* wait_for_child:
*	Waits for a child process to finish execution.
*	Returns the child's exit status or the signal-based exit code
*	if the process was terminated by a signal.
*/
static int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/* search_in_paths:
*	Searches for an executable command in the given PATH directories.
*	Returns the full executable path if found, otherwise NULL.
*/
static char	*search_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = check_path(paths[i], cmd);
		if (full_path)
			return (full_path);
		i++;
	}
	return (NULL);
}

/* find_executable:
*	Finds the full path of a command executable.
*	Handles direct paths and searches through PATH environment
*	directories when needed.
*	Returns the executable path or NULL if not found.
*/
char	*find_executable(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (!cmd || !cmd[0] || !envp)
		return (NULL);
	full_path = handle_direct_path(cmd);
	if (full_path)
		return (full_path);
	path_env = get_env_value("PATH", envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	full_path = search_in_paths(cmd, paths);
	cleanup_paths(paths);
	return (full_path);
}

/* execute_external:
*	Executes an external command using fork and execve.
*	Searches for the executable path before execution.
*	Returns the command exit status or an error code if execution fails.
*/
int	execute_external(t_cmd *cmd, t_shell *shell, int stdin_bk, int stdout_bk)
{
	pid_t		pid;
	char		*path;
	struct stat	st;

	path = find_executable(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd("mcsh: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (free(path), 1);
	if (pid == 0)
	{
		if (stdin_bk != -1)
			close(stdin_bk);
		if (stdout_bk != -1)
			close(stdout_bk);
		execve(path, cmd->args, shell->env);
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("mcsh: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putendl_fd(": Is a directory", STDERR_FILENO);
		}
		else
			perror(path);
		free(path);
		exit(126);
	}
	free(path);
	return (wait_for_child(pid));
}

/* pipe_wait:
*	Waits for all child processes created in a pipeline.
*	Returns the exit status of the last command in the pipeline.
*/
int	pipe_wait(pid_t last_pid, int n)
{
	int		status;
	pid_t	pid;
	int		ret;

	ret = 1;
	while (n-- > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ret = 128 + WTERMSIG(status);
		}
	}
	return (ret);
}
