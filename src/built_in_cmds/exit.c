/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:38 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/07 21:12:53 by omawele          ###   ########.fr       */
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
		cmd_destroy(&cmd);
		shell_destroy(&shell);
		exit((int)code);
	}
	if (!is_valid_exit_arg(cmd->args[1]))
	{
		err_exit(1, cmd->args[1]);
		cmd_destroy(&cmd);
		shell_destroy(&shell);
		exit(2);
	}
	if (cmd->args[2])
		return (err_exit(2, NULL), 1);
	code = ft_atoll(cmd->args[1]);
	code = ((code % 256) + 256) % 256;
	cmd_destroy(&cmd);
	shell_destroy(&shell);
	exit((int)code);
}
