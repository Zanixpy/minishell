/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 21:42:38 by omawele           #+#    #+#             */
/*   Updated: 2026/04/24 17:57:04 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_CMDS
# define BUILT_IN_CMDS

# include "utils.h"
# include "error.h"
# include <limits.h>
# include <linux/limits.h>

int builtin_cd(t_cmd *cmd);
int	builtin_echo(t_cmd *cmd);
int	builtin_pwd(t_cmd *cmd);

#endif