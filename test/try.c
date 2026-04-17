/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:53:22 by omawele           #+#    #+#             */
/*   Updated: 2026/04/07 15:59:05 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>


char *env;

#define NONE "NONE"

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

typedef struct s_philo
{
    int *check;
} t_philo;


void test(t_cmd *cmd)
{
    cmd->path = NULL;
}

int main(void)
{
    int *tetsuya;
    int *kuroko;
    t_philo *philo;
  
    tetsuya = malloc(sizeof(int));
    if (!tetsuya)
        return(1);
    *tetsuya = 0;
    int i = 0;
    philo = malloc(5 * sizeof(t_philo));
    if (!philo)
        return(1);
    while (i < 5)
    {
        philo[i].check = tetsuya;
        i++;
    }
    i = 0;
    while (i < 5)
    {
        printf("1st round pointer : %d\n", *(philo[i].check));
        i++;
    }
    *tetsuya = 42; 
    i = 0;
    while (i < 5)
    {
        printf("2nd round pointer : %d\n", *(philo[i].check));
        i++;
    }
    free(tetsuya);
    free(philo);
    return 0;
}
