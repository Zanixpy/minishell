/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:19:20 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/10 17:53:46 by cakibris         ###   ########.fr       */
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
		perror("could not get current directory");
		return (1);
	}
	if (set_env_var("PWD", cwd, shell) != 0)
		return (1);
	return (0);
}

static int	handle_home_path(t_shell *shell, char **path, char *old_pwd)
{
	*path = get_env_value("HOME", shell->env);
	if (!(*path) || !(*path)[0])
	{
		perror("HOME not set");
		free(old_pwd);
		free(*path);
		return (1);
	}
	return (0);
}

static int	change_directory(char *path, char *old_pwd)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		free(path);
		free(old_pwd);
		return (1);
	}
	free(path);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("could not get current directory");
		return (1);
	}
	old_pwd = ft_strdup(cwd);
	if (!old_pwd)
		return (1);
	if (!cmd->args[1])
	{
		if (handle_home_path(shell, &path, old_pwd) != 0)
			return (1);
	}
	else
		path = ft_strdup(cmd->args[1]);
	if (change_directory(path, old_pwd) != 0)
		return (1);
	if (update_oldpwd(shell, old_pwd) != 0)
		return (1);
	return (update_pwd(shell));
}
