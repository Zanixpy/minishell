/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:15:07 by omawele           #+#    #+#             */
/*   Updated: 2026/04/28 21:49:38 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*search_path_cmd(char **path, char *cmd)
{
	int		i;
	char	*final;
	char	*tmp;

	i = 0;
	final = NULL;
    tmp = ft_strjoin("/", cmd);
    if (!tmp)
	{
        return (NULL);
	}
	while (path[i])
	{
		final = ft_strjoin(path[i], tmp);
		if (!final)
			return (free(tmp), NULL);
		if (access(final, F_OK) == 0)
			break ;
		i++;
		free(final);
		final = NONE;
	}
	return (free(tmp), final);
}
