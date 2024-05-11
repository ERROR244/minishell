/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: error01 <error01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/12 00:44:00 by error01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef enum s_token
{
    Cmd,
    AppendFile,
    HereDocDel,
    Infile,
    OutFile,
    Input,		// '<'
    Output,		// '>'
    Append,		// '>>'
    HereDoc,	// '<<'
    Pipe,		// '|'
    Non
}   t_token;

typedef struct s_data t_data;

typedef struct s_cmds
{
    char *cmd;
    char *flags;
	
    t_token token;
    t_data *data;
	
	struct s_cmds *next;
    struct s_cmds *prev;
}   t_cmds;

struct s_data
{
    char *line;
    char *infile;
    char *outfile;
    char *HRDel;
    char *Appfile;
	char **cmds;
	t_cmds *lst;
};

// lst
t_cmds	*lstlast(t_cmds *lst);
void	lstclear(t_cmds **lst);
t_cmds	*lstnew(char *cmd, t_cmds *stack);

// parsing
void	free_array(char **array);
char	*rm_spaces(char *str);
int     get_list(char **cmd, int size, t_cmds **lst, t_data *data);
void    init_tokens(t_cmds *cmds, int size);
void	parsing(t_data *data);
char	*get_cmd(char *cmd);
char	*get_flags(char *cmd);
int		errors_managment(t_data *data, int flag);
int		check_file(char *str);
int		check_if_NULL(char *str);
int		check_for_pipe(t_cmds *cmds);
int     cmdcheck(char *str);
int		errormsg(char *str);


#endif