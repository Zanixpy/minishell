/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:39:55 by cakibris          #+#    #+#             */
/*   Updated: 2026/06/03 22:13:50 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_env_var(char **env, char *key)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0
			&& env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	env_append(t_shell *shell, char *new_var)
{
	int		len;
	int		i;
	char	**new_env;

	len = 0;
	while (shell->env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (free(new_var), 1);
	i = 0;
	while (i < len)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[len] = new_var;
	new_env[len + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int	set_env_var(char *key, char *value, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*new_var;

	i = find_env_var(shell->env, key);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (1);
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	if (!new_var)
		return (1);
	if (i >= 0)
	{
		free(shell->env[i]);
		shell->env[i] = new_var;
		return (0);
	}
	return (env_append(shell, new_var));
}

int	is_valid_var_name(char *name)
{
	int	i;

	if (!name || !name[0] || ft_isdigit(name[0]))
		return (0);
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_overflow(const char *str)
{
	int					i;
	unsigned long long	nb;
	unsigned long long	limit;

	i = 0;
	nb = 0;
	limit = 9223372036854775807ULL;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		limit = 9223372036854775808ULL;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (limit - (unsigned long long)(str[i] - '0')) / 10)
			return (1);
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (0);
}

long long	ft_atoll(const char *str)
{
	int					i;
	unsigned long long	nb;
	int					sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((long long)(sign * (long long)nb));
}

