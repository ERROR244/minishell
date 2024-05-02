#include "minishell.h"

void handlingsigquit(int signal)
{
    if(signal == SIGQUIT)
    {
        int quit;
        quit = 1; 
    }
}
void handlings(int signal)
{
    if(signal == SIGINT)
        printf("\n./minishell");
}