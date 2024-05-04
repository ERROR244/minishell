#include "minishell.h"

void ft_pwd(char *str)
{
    char *cur;
    char buff[PATH_MAX];
    cur = getcwd(buff, PATH_MAX);
    if( cur != NULL )
        printf("%s\n", cur);
}