/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:16 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/19 11:22:07 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* is_builtin:
*	Checks if a command is a minishell builtin command.
*	Returns 1 if the command is builtin, otherwise 0.
*/
int	is_builtin(char *name)
{
	if (!name || !*name)
		return (0);
	if (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

/* get_env_value:
*	Searches for an environment variable in the env array.
*	Returns a duplicated copy of the variable value if found,
*	otherwise returns NULL.
*/
char	*get_env_value(char *var, char **env)
{
	int	i;
	int	len;

	if (!var || !env)
		return (NULL);
	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

/* handle_heredoc:
*	Reads user input until the delimiter is reached.
*	Stores the heredoc content in a pipe and returns the read end
*	of the pipe.
*	Returns -1 if pipe creation fails.
*/
int	handle_heredoc(char *delim, t_shell *shell, int quoted)
{
	int		fds[2];
	char	*line;

	(void)shell;
	(void)quoted;
	if (pipe(fds) == -1)
		return (-1);
	line = readline("> ");
	while (line && ft_strcmp(line, delim) != 0)
	{
		ft_putendl_fd(line, fds[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fds[1]);
	return (fds[0]);
}

/* setup_heredoc:
*	Creates and prepares the heredoc input for a command.
*	Sets cmd->fdin to the heredoc file descriptor.
*	Returns 0 on success and 1 on error.
*/
int	setup_heredoc(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->heredoc_delim)
		return (0);
	cmd->fdin = handle_heredoc(cmd->heredoc_delim, shell, 0);
	if (cmd->fdin == -1)
		return (1);
	return (0);
}

/* execute_builtin:
*	Executes the corresponding builtin command function.
*	Returns the exit status of the executed builtin command.
*/
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd, shell));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd(cmd, shell));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd, shell));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd, shell));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd, shell));
	return (1);
}
