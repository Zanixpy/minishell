/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 02:55:24 by omawele           #+#    #+#             */
/*   Updated: 2026/03/30 18:37:20 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "utils.h"

char **tokenizer(char *prompt);
int parser(char *prompt, t_cmd *cmd, char *env);

#endif