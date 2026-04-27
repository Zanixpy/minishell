/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:09:15 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 22:36:51 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int convert_token_in_cmd_var(t_cmd **cmd, char **tokens, char **envp, int *pos)
{
	if (*pos == 0 || (*pos > 0 && !ft_strcmp(tokens[*pos - 1], "|")))
	{
		if (set_cmd_and_path(*cmd, tokens[*pos], envp))
			return (1);
	
	}
	else if (!ft_strcmp(tokens[*pos], "|"))
	{
		if (set_cmd_next(cmd))
			return (1);
	}
	else if (is_redirection(tokens[*pos]))
	{
		if (set_cmd_redirections(*cmd, tokens, *pos))
			return (1);
		*pos += 1;
	}
	else if (*pos != 0)
	{
		if (set_cmd_args(*cmd, tokens[*pos]))
			return (1);
	}
	return (0);
}

int tokens_analysis(t_cmd *cmd, char **tokens, char **envp)
{
	t_cmd *tmp;
	char *token;
	int i;

	tmp = cmd;
	i = 0;
	while (tokens[i]) 
	{
		if (convert_token_in_cmd_var(&tmp, tokens, envp, &i))
			return (1);
		i++;
	}
	return (0);
}

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


