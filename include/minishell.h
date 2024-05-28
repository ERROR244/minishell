/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/05/28 11:28:21 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdbool.h>
# include <time.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>


typedef struct s_data t_data;
extern char **myenv;



typedef enum s_token
{
    Cmd,
    AppendFile,
    HereDocDel,
    Infile,
    OutFile,
    Operation,
    NonOperation,
    Input,		// '<'
    Output,		// '>'
    Append,		// '>>'
    HereDoc,	// '<<'
    Pipe,		// '|'
    Non
}   t_token;



typedef struct s_cmds
{
    char **cmd;
	
    t_token token;
    t_token operation;
    t_data *data;

	struct s_cmds *next;
    struct s_cmds *prev;
}   t_cmds;



struct s_data
{
    char    **env;
	char 	**cmds;
    char 	*line;
    char 	*HRDel;
    int		infile;
    int		outfile;
    int		Appfile;
	t_cmds *lst;
};



// lst
t_cmds	    *lstlast(t_cmds *lst);
void	    lstclear(t_cmds **lst);
t_cmds	    *lstnew(char *cmd, t_cmds *stack);
// int		    lstsize(t_cmds *lst);



// parsing
void	    free_array(char **array);
char	    *rm_spaces(char *str);
void         get_list(char **cmd, int size, t_cmds **lst, t_data *data);
void        init_tokens(t_cmds *cmds, int size, t_cmds *lst);
int         parsing(t_data *data);
char	    *get_cmd(char *cmd);
int		    errors_managment(t_data *data, int flag);
int		    check_file(t_cmds *cmds);
int		    check_if_NULL(char *str);
int		    check_for_pipe(t_cmds *cmds);
int         cmdcheck(char *str);
int		    errormsg(char *str);
int		    errormsg_v1(char *str);
int		    errormsg_v2(char *str);
void	    close_used_files(t_data *data);
int         is_spaces(char *str);
void	    non_token(t_cmds *lst);
int         check_for_in_out_put(t_cmds *cmds);
int         check_for_Append_heredoc(t_cmds *cmds);
int         check_access(t_cmds *curr);
int         errormsg(char *str);
int         check_quotation(char *str);
int     	count_words(char const *s);
char	    *ndup(const char *s, size_t n);
void        remove_quotes(t_cmds *lst);
int         dollar_is_in(char *str);
char        *grep_variable_name(char *line);
char        **ft_split_str(char *s1);
void    	expand_variable(t_cmds *cmds);
char        **get_vars(char *cmd);
char        *get_final_line(char **lines, char **vars, char *cmd);
int         dollar_is_in(char *str);
int         count_vars(char *s1);
bool        check_ex(char *str, int size);
// void        ft_free(char **ptr, int i);
char const	*get_position(char const *s);


// executing
void        executing(t_data *data);
void        copieenv(char **env);
void        my_cd(char **com);

// tools
void        exiterror(void);





#endif