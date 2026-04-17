/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:57:20 by omawele           #+#    #+#             */
/*   Updated: 2026/03/30 18:39:07 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "utils.h"


t_cmd *cmd_init(void);
void cmd_destroy_data(t_cmd *cmd);
void cmd_destroy_node(t_cmd *cmd);
void cmd_destroy(t_cmd **cmd);
void cmd_reset(t_cmd *cmd);

#endif