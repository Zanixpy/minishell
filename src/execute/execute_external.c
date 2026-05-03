/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:13 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/04 00:51:14 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	execute_external(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*path;

	path = find_executable(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (free(path), 1);
	if (pid == 0)
	{
		execve(path, cmd->args, shell->env);
		perror(path);
		free(path);
		exit(126);
	}
	free(path);
	return (wait_for_child(pid));
}
