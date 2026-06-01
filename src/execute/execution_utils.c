/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 00:51:07 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/29 11:08:21 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* handle_direct_path:
*	Checks if a command is given as a direct path.
*	Returns a duplicated executable path if accessible,
*	otherwise returns NULL.
*/
char	*handle_direct_path(char *cmd)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

/* join_path_cmd:
*	Joins a PATH directory and command name into a full path.
*	Returns the created path string or NULL on allocation failure.
*/
char	*join_path_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	if (!path || !cmd)
		return (NULL);
	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

/* check_path:
*	Creates and checks a full executable path for a command.
*	Returns the valid executable path if accessible,
*	otherwise returns NULL.
*/
char	*check_path(char *path, char *cmd)
{
	char	*full_path;

	full_path = join_path_cmd(path, cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

/* cleanup_paths:
*	Frees a NULL-terminated array of strings.
*/
void	cleanup_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/* dup_env:
*	Creates a duplicated copy of the environment array.
*	Returns the copied environment or NULL on allocation failure.
*/
char	**dup_env(char **envp)
{
	int		len;
	int		i;
	char	**copy;

	if (!envp)
		return (NULL);
	len = 0;
	while (envp[len])
		len++;
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			copy[i] = NULL;
			cleanup_paths(copy);
			return (NULL);
		}
		i++;
	}
	copy[len] = NULL;
	return (copy);
}
