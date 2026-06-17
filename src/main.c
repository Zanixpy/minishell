/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:06:56 by omawele           #+#    #+#             */
/*   Updated: 2026/06/17 15:22:11 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
void	print_tab(char **tab, char *which)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s[%d] : %s\n", which, i, tab[i]);
		i++;
	}
	if (!tab[i])
		printf("%s[%d] : NULL\n", which, i);
}

void	print_cmd_node(t_cmd *cmd)
{
	if (cmd->cmd)
		printf("cmd : %s\n", cmd->cmd);
	if (cmd->args)
		print_tab(cmd->args, "args");
	if (cmd->path)
		printf("cmd path : %s\n", cmd->path);
	if (cmd->current_dir)
		printf("current_dir : %s\n", cmd->current_dir);
	if (cmd->outfile)
		printf("outfile : %s\n", cmd->outfile);
	if (cmd->infile)
		printf("infile : %s\n", cmd->infile);
	if (cmd->heredoc_delim)
	{
		print_tab(cmd->heredoc_delim, "delim");
		printf("append : %d\n", cmd->append);
	}
	printf("fdin : %d\n", cmd->fdin);
	printf("fdout : %d\n", cmd->fdout);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		printf("============= NODE %d ==================\n", i);
		print_cmd_node(cmd);
		printf("========================================\n");
		cmd = cmd->next;
		i++;
	}
}
*/

int	get_prompt_line(t_cmd *cmd, t_shell *shell)
{
	char	*prompt;
	int		ret;

	prompt = readline("mcsh-1.0# ");
	sigint_signal(shell);
	if (!prompt)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ret = shell->exit_status;
		clean_all(&cmd, &shell);
		exit(ret);
	}
	ret = is_skip(prompt, shell);
	if (ret)
		return (free_str(&prompt), ret);
	ret = parser(prompt, cmd, shell);
	if (ret)
		return (free(prompt), ret);
	shell->input = prompt;
	shell->exit_status = execute_commands(cmd, shell);
	shell->input = NULL;
	return (free(prompt), shell->exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_shell	*shell;
	int		ret;

	(void)ac;
	(void)av;
	setup_signals();
	cmd = cmd_init();
	if (!cmd)
		return (1);
	shell = shell_init(envp);
	if (!shell)
		return (cmd_destroy(&cmd), 1);
	while (1)
	{
		ret = get_prompt_line(cmd, shell);
		if (ret == ERRMALLOC)
			return (clean_all(&cmd, &shell), 1);
		cmd_reset(cmd);
	}
	clean_all(&cmd, &shell);
	return (0);
}
