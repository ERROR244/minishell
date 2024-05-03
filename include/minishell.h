/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/03 20:08:10 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef enum s_token
{
    Cmd,
    File,
    Input,
    Output,
    Append,
    HereDoc,
    Pipe
}   t_token;

typedef struct s_data
{
    char *line;
    char **env;
    char *ptr;
    char *str;
}   t_data;

typedef struct s_cmds
{
    char *cmd;
    struct s_cmds *next;
    struct s_cmds *prev;
}   t_cmds;

// lst
void	lstadd_back(t_cmds **lst, t_cmds *new);
void	lstadd_front(t_cmds **lst, t_cmds *new);
t_cmds	*lstlast(t_cmds *lst);
void	lstclear(t_cmds **lst);
t_cmds	*lstnew(char *cmd, t_cmds *stack);
int		lstsize(t_cmds *lst);

// parsing
void	free_array(char **array);
char	*rm_spaces(char *str);
void    get_list(char **cmd, int size, t_cmds **lst);
void    init_tokens(t_cmds *cmds, int size);
void	parsing(t_data *data);



#endif