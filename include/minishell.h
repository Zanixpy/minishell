/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:10:57 by omawele           #+#    #+#             */
/*   Updated: 2026/05/20 12:29:44 by omawele          ###   ########.fr       */
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

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	char			**args;
	char			*current_dir;
	char			*infile;
	char			*outfile;
	char			*heredoc_delim;
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
 CMD FOLDER 
=====================================*/

/* cmd_init.c */
t_cmd *cmd_init(void);
void cmd_reset(t_cmd *cmd);

/* cmd_destroy.c */
void cmd_destroy_data(t_cmd *cmd);
void cmd_destroy_node(t_cmd *cmd);
void cmd_destroy(t_cmd **cmd);

/*====================================
 ERROR FOLDER 
=====================================*/


/*====================================
 BUILT IN CMD FOLDER 
=====================================*/

/* cd.c */
int builtin_cd(t_cmd *cmd);

/* echo.c */
int	builtin_echo(t_cmd *cmd);

/* env.c */
int	builtin_env(void);

/* pwd.c */
int	builtin_pwd(t_cmd *cmd);

/* unset.c */
int	builtin_unset(t_cmd *cmd);

/* exit.c */
int	builtin_exit(t_cmd *cmd);


/*====================================
 EXECUTE FOLDER
=====================================*/

/* execute.c */
void	reset_redirections(int stdin_backup, int stdout_backup);
int		execute_single_command(t_cmd *cmd, t_shell *shell);

/* execute_cmd.c */
int		is_builtin(char *name);
char	*get_env_value(char *var, char **env);
int		handle_heredoc(char *delim, t_shell *shell, int quoted);
int		setup_heredoc(t_cmd *cmd, t_shell *shell);
int		execute_builtin(t_cmd *cmd, t_shell *shell);

/* execute_external.c */
char	*find_executable(char *cmd, char **envp);
int		execute_external(t_cmd *cmd, t_shell *shell);

/* execution_utils.c */
char	*handle_direct_path(char *cmd);
char	*join_path_cmd(char *path, char *cmd);
char	*check_path(char *path, char *cmd);
void	cleanup_paths(char **paths);

/*====================================
 EXPANDER FOLDER 
=====================================*/

/* expand.c */
char *expand_str(char *s);

/*====================================
 LEXER FOLDER 
=====================================*/

/* lexer.c */
char **lexer(char *prompt);

/*====================================
 PARSER FOLDER 
=====================================*/

/* parser.c */
int parser(char *prompt, t_cmd *cmd, char *env);

/* parser_set_cmd.c */
int set_cmd_and_path(t_cmd *cmd, char *token, char **envp);
int set_cmd_next(t_cmd **cmd);
int set_cmd_redirections(t_cmd *cmd, char **tokens, int *pos);
int set_cmd_args(t_cmd *cmd, char *token);

/* parser_set_cmd_utils.c */
int set_cmd_output(t_cmd *cmd, char *file, int result);
int set_cmd_heredoc(t_cmd *cmd, char *delim);
int set_cmd_input(t_cmd *cmd, char *file);
char	*search_path_cmd(char **path, char *cmd);
/*====================================
 UTILS FOLDER 
=====================================*/

/* bool_utils.c */
int is_space(char *str);
int is_bic(char *str);
int is_quoted(char *s);
int is_redirection(char *s);
// char *is_token(char *str);
int is_special_char(int c);

/* utils.c */
int ft_strcmp(const char *s1, const char *s2);
size_t array_size(char **tab);

/* extract_utils.c */
char *clean_str(char *s, int is_delim);
void fill_var_in_str(char **tmp, int *i, char *var);

/* memory_utils.c */
void	free_char_tab_n(char ***tab, int n);
void	free_char_tab(char ***tab);
char **create_tab(char *str);
char **add_element_in_array(char **tab, char *str);
void free_str(char **s);

/* fd_utils.c */
void close_fds(int fd1, int fd2);


#endif