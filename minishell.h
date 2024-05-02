#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
typedef struct data
{
    char *key;
    char  *value;
    struct  data *next;
}t_data;

typedef struct env
{
    char **env;
    struct env *next;
}t_env;

void    copy_the_envi(char **env, t_data **data);
void    print_environment(t_data *data);
void    ft_cd(char *str, t_data **data);
void    ft_pwd(char *str);


#endif