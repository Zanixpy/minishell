/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 01:18:48 by omawele           #+#    #+#             */
/*   Updated: 2026/03/30 22:28:44 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int is_only_space(char *str)
{
    if (*str)
        return (1);
    while (*str) 
    {
        if (*str != SPACE)
            return (0);
        str++;
    }
    return (1);
}

int isbuilt_in_cmd(char *str)
{
	if (!ft_strncmp("cd", str, 2) || !ft_strncmp("echo", str, 4) ||
		!ft_strncmp("env", str, 3) || !ft_strncmp("exit", str, 4) ||
		!ft_strncmp("export", str, 6) || !ft_strncmp("pwd", str, 3) ||
		!ft_strncmp("unset", str, 5))
		return (0);
	return (1);
}

int istoken(char *str)
{
	int i;
	int  size;

	i = 0;
	size = ft_strlen(str);
	if (size == 1)
	{
		if (*str == GREAT || *str == LESS || *str == PIPE || *str == DOLLAR)
			return (1);
	}
	if (!ft_strncmp(str, GREATGREAT, size) || !ft_strncmp(str, LESSLESS, size))
		return (1);
	return (0);
}
