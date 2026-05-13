#include "external/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

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


static void remove_quotes(char **s, int start_quote, int end_quote)
{
    char *tmp;
    int length;
    int i;
    int j;

    length = strlen(*s) - 2;
    tmp = calloc(length + 1, sizeof(char));
    if (!tmp)
    {
        free(*s);
        *s = NULL;
        return;
    }
    i = 0;
    j = 0;
    while (i < length) 
    {
        if (j == start_quote || j == end_quote)
            j++;
        tmp[i] = (*s)[j];
        i++;
        j++;
    }
    free(*s);
    *s = tmp;
}

static char *clean(char *s)
{
    char quote;
    int i;
    int j;

    s = strdup(s);
    if (!s)
        return (NULL);
    i = -1;
    while (s[++i]) 
    {
        if (s[i] == QUOTE || s[i] == DQUOTE)
        {
            quote = s[i];
            j = i + 1;
            while (s[j] && s[j++] != quote);
            if (s[--j] == quote)
            {
                remove_quotes(&s, i, j);
                if (!s)
                    return (NULL);
                i = j;
            }
        }
    }
    return (s);
}

int main(int ac, char **av)
{
    char *s;

    s = clean(av[1]);
    if (!s)
        return 1;
    printf("s : %s\n", s);
    free(s);
    return 0;
}


