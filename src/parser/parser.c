/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:09:15 by omawele           #+#    #+#             */
/*   Updated: 2026/06/07 21:57:49 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	convert_token_in_cmd_var(t_cmd **cmd, t_shell *shell, char **tokens,
		int *pos)
{
	int	ret;

	ret = 0;
	if (!is_metachar(tokens[*pos]) && ((*pos == 0) || (*pos != 0
		&& !ft_strcmp(tokens[*pos - 1], "|")) || ((*cmd)->cmd
		&& (*cmd)->cmd[0] == '\0')))
	{
		free_str(&(*cmd)->cmd);
		free_str(&(*cmd)->path);
		free_char_tab(&(*cmd)->args);
		ret = set_cmd_and_path(*cmd, shell, tokens[*pos]);
	}
	else if (!ft_strcmp(tokens[*pos], "|"))
	{
		ret = set_cmd_next(cmd, shell, tokens[*pos + 1], *pos);
		if (!ret)
			(*cmd) = (*cmd)->next;
	}
	else if (is_redirection(tokens[*pos]))
		ret = set_cmd_redirections(*cmd, shell, tokens, pos);
	else if (*pos != 0)
		ret = set_cmd_args(*cmd, shell, tokens[*pos]);
	return (ret);
}

static int	tokens_analysis(t_cmd *cmd, t_shell *shell, char **tokens)
{
	t_cmd	*tmp;
	int		i;
	int		ret;

	tmp = cmd;
	i = 0;
	ret = 0;
	while (tokens[i])
	{
		if (is_unclosed_quote(tokens[i]))
			return (perror_syntax(2, cmd, shell));
		ret = convert_token_in_cmd_var(&tmp, shell, tokens, &i);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}

int	parser(char *prompt, t_cmd *cmd, t_shell *shell)
{
	char	**tokens;
	int		ret;

	tokens = lexer(prompt);
	if (!tokens)
		return (ERRMALLOC);
	ret = tokens_analysis(cmd, shell, tokens);
	free_char_tab(&tokens);
	shell->input = prompt;
	return (ret);
}
