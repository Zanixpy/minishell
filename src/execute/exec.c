/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:14:43 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/19 11:23:19 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* execute_commands:
*	Executes one or multiple commands depending on the command count.
*	Executes a single command directly or creates a pipeline when
*	multiple commands are present.
*	Returns the exit status of the executed command(s).
*/
int	execute_commands(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*cur;
	int		count;

	if (!cmd)
		return (1);
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
