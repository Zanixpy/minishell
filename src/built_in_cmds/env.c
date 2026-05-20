/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:54:40 by cakibris          #+#    #+#             */
/*   Updated: 2026/05/10 17:55:50 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return (0);
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
