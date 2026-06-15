/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:31 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/12 14:48:14 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_env_entry(char **env, int i)
{
	free(env[i]);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

static void	unset_one(t_shell *shell, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, len) == 0
			&& (shell->env[i][len] == '=' || shell->env[i][len] == '\0'))
		{
			remove_env_entry(shell->env, i);
			return ;
		}
		i++;
	}
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!shell->env)
		return (0);
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_var_name(cmd->args[i]))
			unset_one(shell, cmd->args[i]);
		else
		{
			ft_putstr_fd("mcsh: unset: `", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
