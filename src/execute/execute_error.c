/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:55:47 by omawele           #+#    #+#             */
/*   Updated: 2026/06/15 16:28:32 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	err_cmd_not_found(char *cmd)
{
	ft_putstr_fd("mcsh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	return (127);
}

void	err_is_dir(char *path)
{
	ft_putstr_fd("mcsh: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": Is a directory", STDERR_FILENO);
}

void	err_heredoc(char *delim)
{
	ft_putstr_fd("mcsh: warning: here-document delimited by "
		"\end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	err_default(char *msg)
{
	ft_putstr_fd("mcsh: ", STDERR_FILENO);
	perror(msg);
}
