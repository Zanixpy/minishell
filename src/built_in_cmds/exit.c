/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:38 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/12 18:01:43 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

long long	ft_atoll(const char *str)
{
	int					i;
	unsigned long long	nb;
	int					sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((long long)(sign * (long long)nb));
}

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
		clean_all(&cmd, &shell);
		exit((int)code);
	}
	if (!is_valid_exit_arg(cmd->args[1]))
	{
		err_exit(1, cmd->args[1]);
		clean_all(&cmd, &shell);
		exit(2);
	}
	if (cmd->args[2])
		return (err_exit(2, NULL), 1);
	code = ft_atoll(cmd->args[1]);
	code = ((code % 256) + 256) % 256;
	clean_all(&cmd, &shell);
	exit((int)code);
}
