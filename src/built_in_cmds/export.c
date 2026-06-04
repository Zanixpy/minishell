/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:35 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/03 22:13:26 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	export_set(t_shell *shell, char *arg)
{
	char	*name;
	char	*value;
	int		len;
	int		ret;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	name = ft_substr(arg, 0, len);
	if (!name)
		return (1);
	if (!is_valid_var_name(name))
	{
		ft_putstr_fd("mcsh: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (free(name), 1);
	}
	if (!arg[len])
		return (free(name), 0);
	value = ft_strdup(arg + len + 1);
	if (!value)
		return (free(name), 1);
	ret = set_env_var(name, value, shell);
	free(name);
	free(value);
	return (ret);
}

static void	sort_env_entries(char **sorted, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	export_print_one(char *entry)
{
	char	*eq;

	ft_putstr_fd("export ", STDOUT_FILENO);
	eq = ft_strchr(entry, '=');
	if (!eq)
	{
		ft_putendl_fd(entry, STDOUT_FILENO);
		return ;
	}
	write(STDOUT_FILENO, entry, eq - entry);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(eq + 1, STDOUT_FILENO);
	ft_putendl_fd("\"", STDOUT_FILENO);
}

static void	export_print(t_shell *shell)
{
	int		len;
	int		i;
	char	**sorted;

	len = 0;
	while (shell->env[len])
		len++;
	sorted = malloc(sizeof(char *) * (len + 1));
	if (!sorted)
		return ;
	i = 0;
	while (i < len)
	{
		sorted[i] = shell->env[i];
		i++;
	}
	sorted[len] = NULL;
	sort_env_entries(sorted, len);
	i = 0;
	while (sorted[i])
		export_print_one(sorted[i++]);
	free(sorted);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;
	int	status;

	if (!cmd->args[1])
	{
		export_print(shell);
		return (0);
	}
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		status = export_set(shell, cmd->args[i]);
		if (status)
			ret = 1;
		i++;
	}
	return (ret);
}
