/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:55:31 by cakibris          #+#    #+#             */
/*   Updated: 2026/04/25 23:36:28 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//needs shell and env and needs remove env function
int	builtin_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		unsetenv(cmd->args[i]);
		i++;
	}
	return (0);
}