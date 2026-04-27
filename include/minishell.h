/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:10:57 by omawele           #+#    #+#             */
/*   Updated: 2026/04/27 22:36:42 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
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

/*====================================
 EXPANDER FOLDER 
=====================================*/


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
int is_built_in_cmd(char *str);
int is_quoted(char *s);
int is_redirection(char *s);
char *is_token(char *str);

/* utils.c */
char *extract_in_quote(char *s);
int ft_strcmp(const char *s1, const char *s2);
int check_quote_count(char *s);
size_t array_size(char **tab);

/* memory_utils.c */
void	free_char_tab_n(char ***tab, int n);
void	free_char_tab(char ***tab);
char **create_tab(char *str);
char **add_element_in_array(char **tab, char *str);

/* parser_utils.c */
char	*search_path_cmd(char **path, char *cmd);



#endif