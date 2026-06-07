/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:14:43 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/29 11:08:01 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* setup_all_heredocs:
 *	Calls setup_heredoc for every command in the list before any
 *	forking begins.  This ensures heredoc fds are ready for both
 *	single commands and pipelines, and that the interactive prompts
 *	are shown to the user before execution starts.
 *	Returns 0 on success and 1 on error.
 */
static int	setup_all_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		if (setup_heredoc(cur, shell))
			return (1);
		cur = cur->next;
	}
	return (0);
}

/* execute_commands:
 *	Sets up heredocs for all commands, then executes them.
 *	Dispatches to a single command or a pipeline based on count.
 *	Returns the exit status of the executed command(s).
 */
int	execute_commands(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*cur;
	int		count;

	if (!cmd)
		return (1);
	if (setup_all_heredocs(cmd, shell))
	{
		if (g_signal == SIGINT)
			return (130);
		return (1);
	}
	cur = cmd;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	if (count == 1)
		return (execute_single_command(cmd, shell));
	return (execute_pipe(cmd, shell));
}
