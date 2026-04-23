#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    t_cmd cmd;
    char *args[] = {"cd", "/", NULL};

    cmd.args = args;
    cmd.cmd = "cd";

    char before[1024];
    char after[1024];

    getcwd(before, 1024);
    printf("BEFORE: %s\n", before);

    int ret = builtin_cd(&cmd);

    getcwd(after, 1024);
    printf("RETURN: %d\n", ret);
    printf("AFTER: %s\n", after);

    return 0;
}