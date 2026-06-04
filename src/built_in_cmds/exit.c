/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:38 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/04 16:57:35 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->args[1])
	{
		status = shell->exit_status;
		shell_destroy_data(shell);
		exit(status);
	}
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		shell_destroy_data(shell);
		exit(255);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	status = ft_atoi(cmd->args[1]) % 256;
	shell_destroy_data(shell);
	exit(status);
}
