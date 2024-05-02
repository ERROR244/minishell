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
    if(ft_strcmp (str, "env") == 0)
    {
        print_environment(data);
    }
    ft_cd(str, &data);
    ft_pwd(str);
    // free(str);
    }
}
