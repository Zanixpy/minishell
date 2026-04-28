/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:09:15 by omawele           #+#    #+#             */
/*   Updated: 2026/04/28 22:23:22 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int convert_token_in_cmd_var(t_cmd **cmd, char **tokens, char **envp, int *pos)
{
	if (*pos == 0 || (*pos != 0 && !ft_strcmp(tokens[*pos - 1], "|")))
	{
		printf("HERE : %s\n", tokens[*pos]);
		if (set_cmd_and_path(*cmd, tokens[*pos], envp))
			return (1);
	}
	else if (!ft_strcmp(tokens[*pos], "|"))
	{
		printf("HERE IN PIPE : %s\n", tokens[*pos]);
		if (set_cmd_next(cmd))
			return (1);
		(*cmd) = (*cmd)->next;
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

static int tokens_analysis(t_cmd *cmd, char **tokens, char **envp)
{
	t_cmd *tmp;
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
	{
		free_char_tab(&tokens);
        return (2);		
	}
	if (tokens_analysis(cmd, tokens, envp))
	{
		free_char_tab(&tokens);
		free_char_tab(&envp);
		return (2);		
	}
	free_char_tab(&tokens);
	free_char_tab(&envp);
    return (0);
}


