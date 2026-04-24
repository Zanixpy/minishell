/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 03:06:56 by omawele           #+#    #+#             */
/*   Updated: 2026/04/24 16:38:51 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

char *env;

// char *get_prompt_line(void)
// {
//     char *prompt_line;
//     char *cur_dir;

//     cur_dir = ft_calloc(100, sizeof(char));
//     if (!cur_dir)
//         return (NULL);
//     if (!getcwd(cur_dir, 100))
//         return (free(cur_dir), NULL);
//     prompt_line = ft_strjoin(cur_dir, "# ");
//     if (!prompt_line)
//         return (free(cur_dir), NULL); 
//     return (prompt_line);
// }


int get_prompt_line(t_cmd *cmd)
{
    (void)cmd;
    char *prompt;

    prompt = readline("mshell-0.2# ");
    if (!prompt)
        return (1);
    else if (ft_isspace(prompt))
        return (1);
    unit_test_lexer(prompt);
    return (0);
}


int main(void)
{
    t_cmd *cmd;

    cmd = cmd_init();
    if (!cmd)
        return (1);
    while (1) 
    {
        if (get_prompt_line(cmd))
            break; 
    }
    cmd_destroy(&cmd);
    return (0);  
}
