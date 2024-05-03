#include "minishell.h"

int main(int ac, char **av, char **env) 
{
    t_data *data = NULL;
    if (ac != 1)
        exit(1);
    copy_the_envi(env, &data);
    while (1)
    {
        char *str = readline("./minishell ");

        if (!str) 
        {
            printf("Failed the allocation\n");
            break;
        }
    if (ft_strcmp(str, "pwd") == 0)
        ft_pwd(str);
    if (ft_strcmp(str, "cd") == 0)
        ft_cd(str, &data);
    if (ft_strcmp(str, "env") == 0)
        print_environment(data);
    // free(str);
    }
}
