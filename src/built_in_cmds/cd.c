/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:19:20 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/03 22:13:38 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_oldpwd(t_shell *shell, char *old_pwd)
{
	if (set_env_var("OLDPWD", old_pwd, shell) != 0)
	{
		free(old_pwd);
		return (1);
	}
	free(old_pwd);
	return (0);
}

static int	update_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putendl_fd("mcsh: cd: error retrieving current directory",
			STDERR_FILENO);
		return (1);
	}
	if (set_env_var("PWD", cwd, shell) != 0)
		return (1);
	return (0);
}

static int	change_directory(char *path, char *old_pwd)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("mcsh: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(NULL);
		free(path);
		free(old_pwd);
		return (1);
	}
	free(path);
	return (0);
}

static int	get_cd_path(t_cmd *cmd, t_shell *shell, char **path, char *old_pwd)
{
	if (!cmd->args[1])
	{
		*path = get_env_value("HOME", shell->env);
		if (!*path || !(*path)[0])
		{
			ft_putendl_fd("mcsh: cd: HOME not set", STDERR_FILENO);
			free(*path);
			free(old_pwd);
			return (1);
		}
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		*path = get_env_value("OLDPWD", shell->env);
		if (!*path || !(*path)[0])
		{
			ft_putendl_fd("mcsh: cd: OLDPWD not set", STDERR_FILENO);
			free(*path);
			free(old_pwd);
			return (1);
		}
		ft_putendl_fd(*path, STDOUT_FILENO);
	}
	else
	{
		*path = ft_strdup(cmd->args[1]);
		if (!*path)
			return (free(old_pwd), 1);
	}
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("mcsh: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putendl_fd("mcsh: cd: error retrieving current directory",
			STDERR_FILENO);
		return (1);
	}
	old_pwd = ft_strdup(cwd);
	if (!old_pwd)
		return (1);
	if (get_cd_path(cmd, shell, &path, old_pwd) != 0)
		return (1);
	if (change_directory(path, old_pwd) != 0)
		return (1);
	if (update_oldpwd(shell, old_pwd) != 0)
		return (1);
	return (update_pwd(shell));
}
