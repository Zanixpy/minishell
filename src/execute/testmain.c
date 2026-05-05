#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	cmd;
	//char	*args[] = {"ls", "-l", NULL};
	//char *args[] = {"ls", NULL};
	//char *args[] = {"ls", "-a", NULL};
	//char *args[] = {"/bin/ls", "-l", NULL};
	//char *args[] = {"./minishell", NULL};
	//char *args[] = {"notacommand", NULL};
	//char *args[] = {"pwd", NULL};
	char *args[] = {"echo", "hello", "world", NULL};
	
	(void)argc;
	(void)argv;
	shell.env = envp;
	shell.exit_status = 0;
	shell.pwd = NULL;
	shell.oldpwd = NULL;
	cmd.args = args;
	cmd.cmd = NULL;
	cmd.path = NULL;
	cmd.current_dir = NULL;
	cmd.infile = NULL;
	cmd.outfile = NULL;
	cmd.heredoc_delim = NULL;
	cmd.fdin = -1;
	cmd.fdout = -1;
	cmd.append = 0;
	cmd.heredoc_quoted = 0;
	cmd.next = NULL;
	execute_single_command(&cmd, &shell);
	return (0);
}
