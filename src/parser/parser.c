/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:09:15 by omawele           #+#    #+#             */
/*   Updated: 2026/04/24 15:52:22 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include <string.h>

// extern char *env;
int parser(char *prompt, t_cmd *cmd, char *env)
{
    char **tokens;
    char **envp;
    
    tokens = lexer(prompt);
    if (!tokens)
        return (2);
    envp = ft_split(env, ':');
    if (!envp)
        return (2);
    return (0);
}

int init_args;

int init_cmd_path(t_cmd *cmd, char *token, char **envp)
{
	cmd->cmd = ft_strdup(token);
	if (!cmd->cmd)
		return (1);
	if (is_built_in_cmd(token))
	{
		cmd->path = ft_strdup("BIC");
		if (!cmd->path)
			return (free(cmd->cmd), 1);		
	}
	else
	{
		cmd->path = search_path_cmd(envp, token);
		if (!cmd->path)
			return (free(cmd->cmd), 1);
	}
	return (0);
}


int init_redirection;



int operator_precedence(t_cmd *cmd, char **tokens, char **envp)
{
	t_cmd *tmp;
	char *token;
	int i;

	tmp = cmd;
	i = 0;
	while (tokens[i]) 
	{
		token = is_token(tokens[i]);
		if (ft_strcmp(token, "PIPE"))
		{
		}
		if (i == 0 || (i > 0 &&  ))
		{
			if (init_cmd_path(tmp, tokens[i], envp))
				return (1);
			// is_pipe = 0;
		}
	}
	return (0);
}


