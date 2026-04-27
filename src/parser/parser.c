/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:09:15 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 17:24:23 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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

int init_args(t_cmd *cmd, char **tokens, int pos)
{
	return (0);	
}

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


int init_redirection(t_cmd *cmd, char **tokens, int pos, int result)
{
	int fd;
	
	if (result == GREAT)
	else if (result == LESS)
	else if (result == GREAT * 2)
	else if (result == LESS * 2)
	
	
	
	return (0);	
}

int operator_precedence(t_cmd *cmd, char **tokens, char **envp)
{
	t_cmd *tmp;
	char *token;
	int i;

	tmp = cmd;
	i = 0;
	while (tokens[i]) 
	{
		if (i == 0 || (i > 0 && !ft_strcmp(tokens[i - 1], "|")))
		{
			if (init_cmd_path(tmp, tokens[i], envp))
				return 1;
		}
		else if (!ft_strcmp(tokens[i], "|"))
		{
			tmp->next = cmd_init();
			if (!tmp->next)
				return (1);
			tmp = tmp->next;
		}
		else if (is_redirection(tokens[i]))
		{
			if (init_redirection(tmp, tokens, i, is_redirection(tokens[i])))
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}


