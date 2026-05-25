/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:10:57 by omawele           #+#    #+#             */
/*   Updated: 2026/05/25 10:47:24 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "../external/libft/libft.h"

# define GREAT '>'
# define GREATGREAT ">>"
# define LESS '<'
# define LESSLESS "<<"
# define PIPE '|'
# define NEWLINE '\n'
# define DOLLAR '$'
# define SPACE ' '
# define QUOTE 39
# define DQUOTE '"'
# define NONE "NONE"
# define ERRMALLOC 15
# define ERRSYNTAX 2
# define EMPTYSTR 98
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	char			**args;
	char			*current_dir;
	char			*infile;
	char			*outfile;
	char			**heredoc_delim;
	int				append;
	int				fdin;
	int				fdout;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	int		exit_status;
	char	*pwd;
	char	*oldpwd;
}	t_shell;

/* main.c */

void print_cmd(t_cmd *cmd);

/*====================================
 SHELL_CMD FOLDER 
=====================================*/

/* shell_cmd_init.c */
t_cmd *cmd_init(void);
void cmd_reset(t_cmd *cmd);
t_shell *shell_init(char **envp);

/* shell_cmd_destroy.c */
void cmd_destroy_data(t_cmd *cmd);
void cmd_destroy_node(t_cmd *cmd);
void cmd_destroy(t_cmd **cmd);
void shell_destroy_data(t_shell *shell);
void shell_destroy(t_shell **shell);

/*====================================
 ERROR FOLDER 
=====================================*/


/*====================================
 BUILT IN CMD FOLDER 
=====================================*/

/* cd.c */
int	builtin_cd(t_cmd *cmd, t_shell *shell);
int	set_env_var(char *key, char *value, t_shell *shell);
/* echo.c */
int	builtin_echo(t_cmd *cmd, t_shell *shell);

/* env.c */
int	builtin_env(t_shell *shell);

/* export.c */
int	builtin_export(t_cmd *cmd, t_shell *shell);

/* pwd.c */
int	builtin_pwd(t_cmd *cmd, t_shell *shell);

/* unset.c */
int	builtin_unset(t_cmd *cmd, t_shell *shell);

/* exit.c */
int	builtin_exit(t_cmd *cmd, t_shell *shell);


/*====================================
 EXECUTE FOLDER
=====================================*/

/* execute.c */
void	reset_redirections(int stdin_backup, int stdout_backup);
int		execute_single_command(t_cmd *cmd, t_shell *shell);

/* execute_cmd.c */
int		is_builtin(char *name);
char	*get_env_value(char *var, char **env);
int	handle_heredoc(char **delim, t_shell *shell, int quoted);
int		setup_heredoc(t_cmd *cmd, t_shell *shell);
int		execute_builtin(t_cmd *cmd, t_shell *shell);

/* execute_external.c */
char	*find_executable(char *cmd, char **envp);
int		execute_external(t_cmd *cmd, t_shell *shell);
int		pipe_wait(pid_t last_pid, int n);

/* execute_pipe.c */
int		execute_pipe(t_cmd *cmds, t_shell *shell);

/* execution_utils.c */
char	*handle_direct_path(char *cmd);
char	*join_path_cmd(char *path, char *cmd);
char	*check_path(char *path, char *cmd);
void	cleanup_paths(char **paths);
char	**dup_env(char **envp);

/* exec.c */
int	execute_commands(t_cmd *commands, t_shell *shell);

/*====================================
 EXPANDER FOLDER 
=====================================*/

/* expand.c */
char *expand_str(char *s, int exit_status);

/*====================================
 LEXER FOLDER 
=====================================*/

/* lexer.c */
char **lexer(char *prompt);

/* lexer_utils.c */
char *clean_prompt(char *prompt);


/*====================================
 PARSER FOLDER 
=====================================*/

/* parser.c */
int parser(char *prompt, t_cmd *cmd, t_shell *shell);

/* parser_set_cmd.c */
int set_cmd_and_path(t_cmd *cmd, t_shell *shell, char *token);
int set_cmd_next(t_cmd **cmd);
int set_cmd_redirections(t_cmd *cmd, t_shell *shell, char **tokens, int *pos);
int set_cmd_args(t_cmd *cmd, t_shell *shell, char *token);

/* parser_set_cmd_utils.c */
int set_cmd_output(t_cmd *cmd, t_shell *shell, char *file, int result);
int set_cmd_heredoc(t_cmd *cmd, char *delim);
int set_cmd_input(t_cmd *cmd, t_shell *shell, char *file);
char	*search_path_cmd(char **path, char *cmd);
char **get_path_split(void);

/*====================================
 UTILS FOLDER 
=====================================*/

/* bool_utils.c */
int is_space(char *str);
int is_bic(char *str);
int is_quoted(char *s);
int is_redirection(char *s);
int is_metachar(char *str);
int is_special_char(int c);

/* utils.c */
int ft_strcmp(const char *s1, const char *s2);
size_t array_size(char **tab);

/* extract_utils.c */
char *clean_str(char *s, int is_delim, int exit_status);
void fill_var_in_str(char **tmp, int *i, char *var);

/* memory_utils.c */
void	free_char_tab_n(char ***tab, int n);
void	free_char_tab(char ***tab);
char **create_tab(char *str);
char **add_element_in_array(char **tab, char *str);
void free_str(char **s);

/* fd_utils.c */
void close_fd(int fd);


#endif