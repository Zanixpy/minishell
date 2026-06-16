/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:16 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/16 20:33:13 by cakibris         ###   ########.fr       */
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

/* execute_builtin:
 *	Executes the corresponding builtin command function.
 *	Returns the exit status of the executed builtin command.
 */
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
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
