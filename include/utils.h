/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 02:55:21 by omawele           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:07 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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


int is_only_space(char *str);
void	free_char_tab(char ***tab);
void	free_char_tab_n(char ***tab, int n);
int isbuilt_in_cmd(char *str);
int istoken(char *str);



#endif