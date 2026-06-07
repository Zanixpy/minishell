/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:59:24 by omawele           #+#    #+#             */
/*   Updated: 2026/06/07 21:36:55 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	err_cd(int code, char *path)
{
	if (code == 1)
		ft_putendl_fd("mcsh: cd: error retrieving current directory",
			STDERR_FILENO);
	else if (code == 2)
	{
		ft_putstr_fd("mcsh: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	else if (code == 3)
		ft_putendl_fd("mcsh: cd: HOME not set", STDERR_FILENO);
	else if (code == 4)
		ft_putendl_fd("mcsh: cd: OLDPWD not set", STDERR_FILENO);
	else if (code == 5)
		ft_putendl_fd("mcsh: cd: too many arguments", STDERR_FILENO);
	else if (code == 6)
		ft_putendl_fd("mcsh: cd: error retrieving current directory",
			STDERR_FILENO);
}

void	err_exit(int code, char *arg)
{
	if (code == 1)
	{
		ft_putstr_fd("mcsh: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else if (code == 2)
		ft_putendl_fd("mcsh: exit: too many arguments", STDERR_FILENO);
}
