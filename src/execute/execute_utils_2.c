/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:31:49 by omawele           #+#    #+#             */
/*   Updated: 2026/06/15 15:36:34 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_cleanup_exit(t_cmd *head, t_shell *shell, int status)
{
	clean_all(&head, &shell);
	exit(status);
}

int	handle_heredoc_cond(char **line, char *delim)
{
	if (!(*line))
	{
		err_heredoc(delim);
		return (1);
	}
	if (ft_strcmp(*line, delim) == 0)
	{
		free_str(line);
		return (1);
	}
	return (0);
}
