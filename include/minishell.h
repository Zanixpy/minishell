/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:10:57 by omawele           #+#    #+#             */
/*   Updated: 2026/06/12 14:45:31 by cakibris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../external/libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define GREAT '>'
# define GREATGREAT ">>"
# define LESS '<'
# define LESSLESS "<<"
# define PIPE '|'
# define DOLLAR '$'
# define SPACE ' '
# define QUOTE 39
# define DQUOTE '"'
# define ERRMALLOC 15
# define ERRSYNTAX 2
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_cmd
{
	char						*cmd;
	char						*path;
	char						**args;
	char						*current_dir;
	char						*infile;
	char						*outfile;
	char						**heredoc_delim;
	int							heredoc_quoted;
	int							append;
	int							fdin;
	int							fdout;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_shell
{
	char						**env;
	int							exit_status;
	char						*pwd;
	char						*oldpwd;
	char						*input;
}								t_shell;

/* signals.c */
extern volatile sig_atomic_t	g_signal;
void							setup_signals(void);
void							reset_signals_for_child(void);
void							ignore_signals_in_parent(void);

/* main.c */

void							print_cmd(t_cmd *cmd);

/*====================================
 SHELL_CMD FOLDER
=====================================*/

/* shell_cmd_init.c */
t_cmd							*cmd_init(void);
void							cmd_reset(t_cmd *cmd);
t_shell							*shell_init(char **envp);

/* shell_cmd_destroy.c */
void							cmd_destroy_data(t_cmd *cmd);
void							cmd_destroy_node(t_cmd *cmd);
void							cmd_destroy(t_cmd **cmd);
void							shell_destroy_data(t_shell *shell);
void							shell_destroy(t_shell **shell);

/*====================================
 BUILT IN CMD FOLDER
=====================================*/

/* built_in_error.c */
void							err_cd(int code, char *path);
void							err_exit(int code, char *arg);

/* built_in_utils.c */
int								set_env_var(char *key, char *value,
									t_shell *shell);
int								is_valid_var_name(char *name);
int								is_overflow(const char *str);
long long						ft_atoll(const char *str);

/* cd.c */
int								builtin_cd(t_cmd *cmd, t_shell *shell);

/* echo.c */
int								builtin_echo(t_cmd *cmd, t_shell *shell);

/* env.c */
int								builtin_env(t_shell *shell);

/* export.c */
int								builtin_export(t_cmd *cmd, t_shell *shell);

/* pwd.c */
int								builtin_pwd(t_cmd *cmd, t_shell *shell);

/* unset.c */
int								builtin_unset(t_cmd *cmd, t_shell *shell);

/* exit.c */
int								builtin_exit(t_cmd *cmd, t_shell *shell);

/*====================================
 EXECUTE FOLDER
=====================================*/

/* execute.c */
void							reset_redirections(int *stdin_backup,
									int *stdout_backup);
int								execute_single_command(t_cmd *cmd,
									t_shell *shell);

/* execute_cmd.c */
char							*get_env_value(char *var, char **env);
int								handle_heredoc(char **delim, t_shell *shell,
									int quoted);
int								setup_heredoc(t_cmd *cmd, t_shell *shell);
int								execute_builtin(t_cmd *cmd, t_shell *shell);

/* execute_external.c */
char							*find_executable(char *cmd, char **envp);
int								execute_external(t_cmd *cmd, t_shell *shell,
									int stdin_bk, int stdout_bk);
int								pipe_wait(pid_t last_pid, int n);

/* execute_utils_2.c */
void							child_cleanup_exit(t_cmd *head, t_shell *shell,
									int status);
int handle_heredoc_cond(char **line, char *delim);
				

/* execute_pipe.c */
int								execute_pipe(t_cmd *cmds, t_shell *shell);

/* execution_utils.c */
char							*handle_direct_path(char *cmd);
char							*join_path_cmd(char *path, char *cmd);
char							*check_path(char *path, char *cmd);
void							cleanup_paths(char **paths);
char							**dup_env(char **envp);

/* exec.c */
int								execute_commands(t_cmd *commands,
									t_shell *shell);

/* execute_error.c */
int								err_cmd_not_found(char *cmd);
void							err_is_dir(char *path);
void							err_heredoc(char *delim);

/*====================================
 EXPANDER FOLDER
=====================================*/

/* expand.c */
char							*expand_str(char *s, int exit_status,
										char **envp);

/*====================================
 LEXER FOLDER
=====================================*/

/* lexer.c */
char							**lexer(char *prompt);

/* lexer_utils.c */
char							*clean_prompt(char *prompt);

/*====================================
 ERROR FOLDER
=====================================*/

/* parser_error.c */
int								perror_syntax(int code, t_cmd *cmd,
									t_shell *shell);
int								perror_redir_meta(char *token, t_shell *shell);

/*====================================
 PARSER FOLDER
=====================================*/

/* parser.c */
int								parser(char *prompt, t_cmd *cmd,
									t_shell *shell);

/* parser_set_cmd.c */
int								set_cmd_and_path(t_cmd *cmd, t_shell *shell,
									char *token);
int								set_cmd_redirections(t_cmd *cmd, t_shell *shell,
									char **tokens, int *pos);
int								set_cmd_next(t_cmd **cmd, t_shell *shell,
									char *token, int pos);
int								set_cmd_args(t_cmd *cmd, t_shell *shell,
									char *token);

/* parser_set_cmd_utils.c */
int								set_cmd_output(t_cmd *cmd, t_shell *shell,
									char *file, int result);
int								set_cmd_heredoc(t_cmd *cmd, t_shell *shell,
									char *delim);
int								set_cmd_input(t_cmd *cmd, t_shell *shell,
									char *file);
char							*search_path_cmd(char **path, char *cmd);
char							**get_path_split(void);

/*====================================
 UTILS FOLDER
=====================================*/

/* bool_utils.c */
int								is_bic(char *str);
int								is_redirection(char *s);
int								is_metachar(char *str);
int								is_special_char(int c);
int								is_unclosed_quote(char *s);

/* utils.c */
int								ft_strcmp(const char *s1, const char *s2);
size_t							array_size(char **tab);
int								is_skip(char *prompt, t_shell *shell);
int								is_space(char *str);
int								is_unexpand_char(char c);

/* extract_utils.c */
char							*clean_str(char *s, int is_delim,
										int exit_status, char **envp);
void							fill_var_in_str(char **tmp, int *i, char *var);

/* memory_utils.c */
void							free_char_tab_n(char ***tab, int n);
void							free_char_tab(char ***tab);
char							**create_tab(char *str);
char							**add_element_in_array(char **tab, char *str);
void							free_str(char **s);

/* fd_utils.c */
void							close_fd(int fd);
void							delete_file(t_cmd *cmd);
void							close_pipe(int fd1, int fd2);
void							dup_fd(int newfd, int oldfd);

#endif