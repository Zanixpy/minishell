/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:38 by cakibris          #+#    #+#             */
/*   Updated: 2026/04/27 23:24:10 by cakibris         ###   ########.fr       */
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

int	builtin_exit(t_cmd *cmd)
{
	int	status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	status = 0;
	if (!cmd->args[1])
		exit(0);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	status = ft_atoi(cmd->args[1]);
	if (cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit(status % 256);
	return (0);
}