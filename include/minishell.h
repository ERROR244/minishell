/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/17 15:05:39 by ksohail-         ###   ########.fr       */
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

    // Double linked list
	struct s_cmds *next;
    struct s_cmds *prev;

	// BST
    struct s_cmds *left;
    struct s_cmds *right;
}   t_cmds;

struct s_data
{
	char 	**cmds;
    char 	*line;
    char 	*HRDel;
    int		infile;
    int		outfile;
    int		Appfile;
	t_cmds *lst;
};

// lst
t_cmds	*lstlast(t_cmds *lst);
void	lstclear(t_cmds **lst);
t_cmds	*lstnew(char *cmd, t_cmds *stack);
int		lstsize(t_cmds *lst);

// parsing
void	free_array(char **array);
char	*rm_spaces(char *str);
void     get_list(char **cmd, int size, t_cmds **lst, t_data *data);
void    init_tokens(t_cmds *cmds, int size);
void	parsing(t_data *data);
char	*get_cmd(char *cmd);
char	*get_flags(char *cmd);
int		errors_managment(t_data *data, int flag);
int		check_file(t_cmds *cmds);
int		check_if_NULL(char *str);
int		check_for_pipe(t_cmds *cmds);
int     cmdcheck(char *str);
int		errormsg(char *str);
void	close_used_files(t_data *data);
int     is_spaces(char *str);
void	non_token(t_cmds *lst);


#endif