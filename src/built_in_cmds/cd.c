#include "../../include/minishell.h"

static int update_oldpwd(char *old_pwd)
{
    if (setenv("OLDPWD", old_pwd, 1) != 0)
    {
        perror("cd");
        free(old_pwd);
        return (1);
    }
    free(old_pwd);
    return (0);
}

static int update_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        perror("cd");
        return (1);
    }
    if (setenv("PWD", cwd, 1) != 0)
        return (1);
    return (0);
}

static int handle_home_path(char **path, char *old_pwd)
{
    *path = getenv("HOME");
    if (!(*path) || !(*path)[0])
    {
        write(2, "cd: HOME not set\n", 17);
        free(old_pwd);
        return (1);
    }
    *path = strdup(*path); // important: duplicate!
    return (0);
}

static int change_directory(char *path, char *old_pwd)
{
    if (chdir(path) != 0)
    {
        perror("cd");
        free(path);
        free(old_pwd);
        return (1);
    }
    free(path);
    return (0);
}

int builtin_cd(t_cmd *cmd)
{
    char    *path;
    char    *old_pwd;
    char    cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        perror("cd");
        return (1);
    }

    old_pwd = strdup(cwd);
    if (!old_pwd)
        return (1);

    if (!cmd->args || !cmd->args[1])
    {
        if (handle_home_path(&path, old_pwd) != 0)
            return (1);
    }
    else
        path = strdup(cmd->args[1]);

    if (!path)
        return (free(old_pwd), 1);

    if (change_directory(path, old_pwd) != 0)
        return (1);

    if (update_oldpwd(old_pwd) != 0)
        return (1);

    return (update_pwd());
}