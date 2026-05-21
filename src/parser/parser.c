/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:09:15 by omawele           #+#    #+#             */
/*   Updated: 2026/05/21 16:16:41 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int convert_token_in_cmd_var(t_cmd **cmd, char **tokens, char **envp, int *pos)
{
	int ret;
	
	if (*pos == 0 || (*pos != 0 && !ft_strcmp(tokens[*pos - 1], "|")) 
		|| ((*cmd)->cmd && (*cmd)->cmd[0] == '\0'))
		ret = set_cmd_and_path(*cmd, tokens[*pos], envp);
	else if (!ft_strcmp(tokens[*pos], "|"))
	{
		ret = set_cmd_next(cmd);
		if (!ret)
			(*cmd) = (*cmd)->next;
	}
	else if (is_redirection(tokens[*pos]))
		ret = set_cmd_redirections(*cmd, tokens, pos);
	else if (*pos != 0)
		ret = set_cmd_args(*cmd, tokens[*pos]);
	return (ret);
}

static int tokens_analysis(t_cmd *cmd, char **tokens, char **envp)
{
	t_cmd *tmp;
	int i;
	int ret;

	tmp = cmd;
	i = 0;
	ret = 0;
	while (tokens[i]) 
	{
		ret = convert_token_in_cmd_var(&tmp, tokens, envp, &i);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}

int parser(char *prompt, t_cmd *cmd, char *env)
{
    char **tokens;
    char **envp;
	int ret;
    
    tokens = lexer(prompt);
    if (!tokens)
        return (ERRMALLOC);
    envp = ft_split(env, ':');
    if (!envp)
		return (free_char_tab(&tokens), ERRMALLOC);
	ret = tokens_analysis(cmd, tokens, envp);
	free_char_tab(&tokens);
	free_char_tab(&envp);
    return (ret);
}


