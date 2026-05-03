/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakibris <cakibris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:10:57 by omawele           #+#    #+#             */
/*   Updated: 2026/05/04 00:38:15 by cakibris         ###   ########.fr       */
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
# define PATH_MAX 4096

typedef struct s_cmd
{
    char    *cmd;          
    char    *path;          // Le chemin vers l'exécutable (/bin/ls)
    char    **args;         // Le tableau d'arguments
    char    *current_dir;   // Ton PWD au moment du lancement
    int     fdin;           // Pour les redirections < | <<
    int     fdout;          // Pour les redirections > | >>
    struct s_cmd *next;     // Si tu as des pipes
} t_cmd;

typedef struct s_shell
{
	char	**env;
	int		exit_status;
	char	*pwd;
	char	*oldpwd;
}	t_shell;

typedef struct s_command
{
	char	**args;          // ["ls", "-l"]
	char	*infile;         // "< file"
	char	*outfile;        // "> file"
	int		append;          // ">>"
	char	*heredoc_delim; // "<< EOF"
	int		heredoc_quoted;

	int		input_fd;
	int		output_fd;

	struct s_command *next;  // for pipes
}	t_command;

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
int	builtin_pwd(t_cmd *cmd);

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
int		execute_single_command(t_command *cmd, t_shell *shell);

/* execute_cmd.c */
int		is_builtin(char *name);
char	*get_env_value(char *var, char **env);
int		handle_heredoc(char *delim, t_shell *shell, int quoted);
int		setup_heredoc(t_command *cmd, t_shell *shell);
int		execute_builtin(t_command *cmd, t_shell *shell);

/* execute_external.c */
char	*find_executable(char *cmd, char **envp);
int		execute_external(t_command *cmd, t_shell *shell);

/* execution_utils.c */
char	*handle_direct_path(char *cmd);
char	*join_path_cmd(char *path, char *cmd);
char	*check_path(char *path, char *cmd);
void	cleanup_paths(char **paths);

/*====================================
 EXPANDER FOLDER 
=====================================*/

/* expand.c */
char *expand_var(char *s);

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
int set_cmd_redirections(t_cmd *cmd, char **tokens, int pos);
int set_cmd_args(t_cmd *cmd, char *token);

/* parser_utils.c */
char	*search_path_cmd(char **path, char *cmd);

/*====================================
 UTILS FOLDER 
=====================================*/

/* bool_utils.c */
int is_space(char *str);
int is_bic(char *str);
int is_quoted(char *s);
int is_redirection(char *s);
char *is_token(char *str);
int is_var(char *s);
int is_special_token(int c);
int is_there_quote(char *s);

/* utils.c */
int ft_strcmp(const char *s1, const char *s2);
int check_quote_count(char *s);
size_t array_size(char **tab);

/* extract_utils.c */
char *extract_str(char *s);
char *clean_str(char *s);

/* memory_utils.c */
void	free_char_tab_n(char ***tab, int n);
void	free_char_tab(char ***tab);
char **create_tab(char *str);
char **add_element_in_array(char **tab, char *str);
void free_str(char **s);





#endif