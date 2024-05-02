#include "minishell.h"

void ft_pwd(char *str)
{
    char cur[PATH_MAX];
    if(ft_strcmp(str, "pwd") == 0)
    {
        getcwd(cur, sizeof(cur));
        printf("%s\n", cur);
    }
}