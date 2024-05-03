#include "minishell.h"

void ft_pwd(char *str)
{
    char cur[PATH_MAX];
    getcwd(cur, sizeof(cur));
    printf("%s\n", cur);
}