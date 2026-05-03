/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:16 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/04 00:51:17 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	setup_heredoc(t_command *cmd, t_shell *shell)
{
	if (!cmd->heredoc_delim)
		return (0);
	cmd->input_fd = handle_heredoc(cmd->heredoc_delim, shell,
			cmd->heredoc_quoted);
	if (cmd->input_fd == -1)
		return (1);
	return (0);
}

int	execute_builtin(t_command *cmd, t_shell *shell)
{
	t_cmd	blt;

	ft_bzero(&blt, sizeof(t_cmd));
	blt.args = cmd->args;
	(void)shell;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(&blt));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd(&blt));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env());
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(&blt));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(&blt));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(&blt));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	return (1);
}
