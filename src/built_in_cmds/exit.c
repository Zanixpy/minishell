/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:38 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/03 23:35:23 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_exit_arg(char *str)
{
	int	i;

	if (is_overflow(str))
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
	long long	code;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->args[1])
	{
		code = shell->exit_status;
		cmd_destroy_data(cmd);
		cmd_destroy_node(cmd);
		free(cmd);
		shell_destroy_data(shell);
		free(shell);
		exit((int)code);
	}
	if (!is_valid_exit_arg(cmd->args[1]))
	{
		ft_putstr_fd("mcsh: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		cmd_destroy_data(cmd);
		cmd_destroy_node(cmd);
		free(cmd);
		shell_destroy_data(shell);
		free(shell);
		exit(2);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("mcsh: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	code = ft_atoll(cmd->args[1]);
	code = ((code % 256) + 256) % 256;
	cmd_destroy_data(cmd);
	cmd_destroy_node(cmd);
	free(cmd);
	shell_destroy_data(shell);
	free(shell);
	exit((int)code);
}
