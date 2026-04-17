/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:09:15 by omawele           #+#    #+#             */
/*   Updated: 2026/03/30 22:55:45 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include <string.h>

// extern char *env;
int parser(char *prompt, t_cmd *cmd, char *env)
{
    char **tokens;
    char **envp;
    
    tokens = tokenizer(prompt);
    if (!tokens)
        return (2);
    envp = ft_split(env, ':');
    if (!envp)
        return (2);
    return (0);
}

char	*search_path_cmd(char **path, char *cmd)
{
	int		i;
	char	*final;
	char	*tmp;

	if (isbuilt_in_cmd(cmd))
		return (NONE);
	i = 0;
	final = NULL;
    tmp = ft_strjoin("/", cmd);
    if (!tmp)
        return (NULL);
	while (path[i])
	{
		final = ft_strjoin(tmp, cmd);
		if (!final)
			return (free(tmp), NULL);
		if (access(final, F_OK) == 0)
			break ;
		i++;
		free(final);
		final = NONE;
	}
	return (free(cmd), final);
}

int operator_precedence(t_cmd *cmd, char **tokens, char **envp)
{
	int i;
	int j;

	i = 0;
	cmd->cmd = tokens[i];
	cmd->path = search_path_cmd(envp, tokens[i]);
	if (!cmd->path)
		return (1);
	while (tokens[i]) 
	{

	
	}
	return (0);
}


