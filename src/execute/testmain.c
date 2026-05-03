#include "../../include/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_command cmd;
	char *args[] = {"ls", "-l", NULL};

	(void)argc;
	(void)argv;

	// fake shell
	shell.env = envp;
	shell.exit_status = 0;
	shell.pwd = NULL;
	shell.oldpwd = NULL;

	// fake command
	cmd.args = args;
	cmd.infile = NULL;
	cmd.outfile = NULL;
	cmd.heredoc_delim = NULL;
	cmd.input_fd = -1;
	cmd.output_fd = -1;
	cmd.append = 0;
	cmd.next = NULL;

	execute_single_command(&cmd, &shell);
	return (0);
}