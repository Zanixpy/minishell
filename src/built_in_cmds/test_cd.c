#include "../../include/minishell.h"

int main(void)
{
	t_cmd	cmd;

	cmd.cmd = "pwd";
	cmd.args = NULL;
	cmd.path = NULL;
	cmd.current_dir = NULL;
	cmd.next = NULL;
	cmd.fdin = -2;
	cmd.fdout = -2;

	builtin_pwd(&cmd);
	return (0);
}