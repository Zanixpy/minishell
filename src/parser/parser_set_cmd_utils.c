/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:34:39 by omawele           #+#    #+#             */
/*   Updated: 2026/06/17 12:59:03 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_full_path(char *path_env, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = check_path(paths[i], cmd);
		if (full_path)
			return (free_char_tab(&paths), full_path);
		i++;
	}
	free_char_tab(&paths);
	if (!full_path)
		full_path = ft_strdup(cmd);
	return (full_path);
}

int	set_cmd_output(t_cmd *cmd, t_shell *shell, char *file, int result)
{
	free_str(&cmd->outfile);
	if (is_metachar(file))
		return (perror_redir_meta(file, shell));
	cmd->outfile = clean_str(file, 0, shell->exit_status, shell->env);
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
	cmd->infile = clean_str(file, 0, shell->exit_status, shell->env);
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
	clean_delim = clean_str(delim, 1, 0, NULL);
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
