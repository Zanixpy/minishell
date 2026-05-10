/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:35 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/10 17:56:02 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	env_add(t_shell *shell, char *entry)
{
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while (shell->env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (free(entry), 1);
	i = 0;
	while (i < len)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[len] = entry;
	new_env[len + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	export_set(t_shell *shell, char *arg)
{
	char	*entry;
	int		len;
	int		i;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (!arg[len])
		return (0);
	entry = ft_strdup(arg);
	if (!entry)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, len) == 0
			&& shell->env[i][len] == '=')
			return (free(shell->env[i]), shell->env[i] = entry, 0);
		i++;
	}
	return (env_add(shell, entry));
}

static void	export_print(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd->args[1])
	{
		export_print(shell);
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (export_set(shell, cmd->args[i]))
			return (1);
		i++;
	}
	return (0);
}
