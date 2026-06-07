/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:34:39 by omawele           #+#    #+#             */
/*   Updated: 2026/05/28 14:20:30 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_path_cmd(char **path, char *cmd)
{
	int		i;
	char	*final;
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (NULL);
	final = NULL;
	i = -1;
	while (path[++i])
	{
		final = ft_strjoin(path[i], tmp);
		if (!final)
			return (free(tmp), NULL);
		if (access(final, F_OK) == 0)
			break ;
		free(final);
		final = NULL;
	}
	free(tmp);
	if (!final)
		final = ft_strdup(cmd);
	return (final);
}

char	**get_path_split(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}

int	set_cmd_output(t_cmd *cmd, t_shell *shell, char *file, int result)
{
	free_str(&cmd->outfile);
	if (is_metachar(file))
		return (perror_redir_meta(file, shell));
	cmd->outfile = clean_str(file, 0, shell->exit_status);
	if (!cmd->outfile)
		return (ERRMALLOC);
	if (result == GREAT)
	{
		close_fd(cmd->fdout);
		cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		close_fd(cmd->append);
		cmd->append = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (0);
}

int	set_cmd_input(t_cmd *cmd, t_shell *shell, char *file)
{
	free_str(&cmd->infile);
	if (is_metachar(file))
		return (perror_redir_meta(file, shell));
	cmd->infile = clean_str(file, 0, shell->exit_status);
	if (!cmd->infile)
		return (ERRMALLOC);
	close_fd(cmd->fdin);
	cmd->fdin = open(cmd->infile, O_RDONLY);
	return (0);
}

int	set_cmd_heredoc(t_cmd *cmd, t_shell *shell, char *delim)
{
	char	**tmp;
	char	*clean_delim;

	if (is_metachar(delim))
		return (perror_redir_meta(delim, shell));
	cmd->heredoc_quoted = (ft_strchr(delim, QUOTE) != NULL || ft_strchr(delim,
				DQUOTE) != NULL);
	clean_delim = clean_str(delim, 1, 0);
	if (!clean_delim)
		return (ERRMALLOC);
	if (!cmd->heredoc_delim)
		cmd->heredoc_delim = create_tab(clean_delim);
	else
	{
		tmp = cmd->heredoc_delim;
		cmd->heredoc_delim = add_element_in_array(tmp, clean_delim);
		free_char_tab(&tmp);
	}
	free(clean_delim);
	if (!cmd->heredoc_delim)
		return (ERRMALLOC);
	return (0);
}
