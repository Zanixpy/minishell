/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:16 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/12 14:48:17 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
 *	Reads user input until the delimiter is matched or EOF.
 *	Expands variables in each line unless the delimiter was quoted.
 *	Prints a warning on EOF and aborts on SIGINT.
 *	The pipe read end is returned and becomes the command's stdin.
 *	Returns -1 on error or interrupt.
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

int	handle_heredoc(char **delim, t_shell *shell, int quoted)
{
	int		fds[2];
	char	*line;

	if (!delim || !*delim || !**delim)
		return (-1);
	if (pipe(fds) == -1)
		return (-1);
	g_signal = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			close_pipe(fds[1], fds[0]);
			return (free(line), -1);
		}
		if (handle_heredoc_cond(&line, *delim))
			break ;
		if (heredoc_write_line(line, fds[1], shell, quoted))
		{
			free(line);
			close_pipe(fds[1], fds[0]);
			return (-1);
		}
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}

/* setup_heredoc:
 *	Reads ALL heredoc delimiters in order (left to right), as bash does.
 *	Each heredoc is fully consumed; only the last one's fd becomes stdin.
 *	Earlier fds are closed after reading so memory is not leaked.
 *	Returns 0 on success and 1 on error.
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
		if (cmd->fdin >= 0)
			close(cmd->fdin);
		cmd->fdin = fd;
		i++;
	}
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
