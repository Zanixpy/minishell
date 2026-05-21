/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:34:39 by omawele           #+#    #+#             */
/*   Updated: 2026/05/21 16:26:46 by omawele          ###   ########.fr       */
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
		final = ft_strdup(cmd);
		if (!final)
			return (free(tmp), NULL);			
	}
	return (free(tmp), final);
}

int set_cmd_output(t_cmd *cmd, char *file, int result)
{
    free_str(&cmd->outfile);
    cmd->outfile = clean_str(file, 0);
    if (!cmd->outfile)
        return (ERRMALLOC);
    else if (*cmd->outfile == '\0')
        return (EMPTYSTR);
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

int set_cmd_input(t_cmd *cmd, char *file)
{
    free_str(&cmd->infile);
    cmd->infile = clean_str(file, 0);
    if (!cmd->infile)
        return (ERRMALLOC);
    else if (*cmd->infile == '\0')
        return (free(cmd->infile), EMPTYSTR);
    close_fd(cmd->fdin);
    cmd->fdin = open(cmd->infile, O_RDONLY);     
    return (0); 
}

int set_cmd_heredoc(t_cmd *cmd, char *delim)
{
    cmd->heredoc_delim = clean_str(delim, 1);
    if (!cmd->heredoc_delim)
        return (ERRMALLOC);
    return (0);  
}



