/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 02:55:24 by omawele           #+#    #+#             */
/*   Updated: 2026/04/26 17:46:32 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "utils.h"
#include "cmd.h"

char **lexer(char *prompt);
int parser(char *prompt, t_cmd *cmd, char *env);

#endif