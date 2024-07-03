/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/02 13:15:41 by ohassani         ###   ########.fr       */
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

typedef struct s_signal
{
    int ret;
    bool flag_sig;
    int pipef;
    int sig;
    bool flag_heredoc;
    int ff;

}   t_signal;

extern t_signal my_signal;

extern bool flag_sig;
// extern bool flag_data;
extern int ret;
extern char Gstr[100][100];




typedef struct s_env
{
    char    *var_name;

	struct s_env *next;
    struct s_env *prev;
}   t_env;

typedef enum s_token
{
    Cmd,
    AppendFile,
    HereDocDel,
    Infile,
    OutFile,
    Operation,
    NonOperation,
    Input,
    Output,
    Append,
    HereDoc,
    Pipe,
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

typedef struct s_slist
{
    char    *cmd;

    t_token token;

	struct s_slist *next;
    struct s_slist *prev;
}   t_slist;

typedef struct s_command
{
    char **cmd;

    t_slist  *infile; 
    t_slist  *outfile;

	struct s_command *next;
    struct s_command *prev;
}   t_command;

struct s_data
{
    int         fd[2];
    int         *pid;
    int         k;
    int         fd_in;
    char        **env;
	char 	    **cmds;
    char 	    *line;
    
    bool        path_flag;
    bool        flag;
    
    t_env       *list_env;
	t_cmds      *lst;
    t_command   *list;
};



// lst
t_cmds	    *lstlast(t_cmds *lst);
void	    lstclear(t_cmds **lst);
t_cmds	    *lstnew(char *cmd, t_cmds *stack, char **str);

char	*ft_strjoin3(char const *s1, char c, char const *s2);

// parsing
void    signal_handler(void);
void signal_hand2();
void sig_pipe(int signal);
void handler_before(void);
void	    free_array(char **array);
char	    *rm_spaces(char *str);
void        get_list(char **cmd, int size, t_cmds **lst, t_data *data);
void        init_tokens(t_cmds *cmds, int size, t_cmds *lst);
void        parsing(t_data *data);
char	    *get_cmd(char *cmd);
int		    errors_managment(t_data *data, int flag);
int		    check_file(t_cmds *cmds);
int		    check_if_NULL(char *str);
int		    check_for_pipe(t_cmds *cmds);
int         cmdcheck(char *str);
int		    errormsg(char *str);
int		    errormsg_v1(char *str);
void printsignalsc(int signal);
int		    errormsg_v2(char *str);
// void	    close_used_files(t_data *data);
int         is_spaces(char *str);
void	    non_token(t_cmds *lst);
int         check_for_in_out_put(t_cmds *cmds);
int         check_for_Append_heredoc(t_cmds *cmds);
// int         check_access(t_cmds *curr);
int         errormsg(char *str);
int         check_quotation(char *str);
int     	count_words(char const *s);
char	    *ndup(const char *s, size_t n);
void        remove_quotes(t_cmds *lst);
int         dollar_is_in(char *str);
char        *grep_variable_name(char *line);
char        **ft_split_str(char *s1);
char    	*expand_variable(char *str, t_data *data);
char        **get_vars(char *cmd);
char        *get_final_line(char **lines, char **vars, char *cmd);
int         dollar_is_in(char *str);
int         count_vars(char *s1);
bool        check_ex(char *str, int size);
char        *check_tabs(char *str, int i, int j, t_data *data);
// void     ft_free(char **ptr, int i);
char const	*get_position(char const *s);
size_t      get_size(char *str);
char        *get_string(char *str, size_t i, size_t k, size_t size);

int run_builtins(int c, t_command *command, t_data *data, int flag);
int hand_the_redirectionin(t_command *lst); //, int in, int out)
 void    ft_handle_sigint(int sig);

t_slist     *nodes_last(t_slist *lst);
t_command	*command_last(t_command *lst);
t_command	*command_new(t_command *lst);
t_command	*get_command(t_cmds *lst);
t_command	*get_commands(t_cmds *lst);
void	    commands_clear(t_command **lst);
void        ft_clear(t_data *data);



// tmp
void	    print_array(char **str);
void	    printlist(void *tmp);
int         ft_fork(void);
void        ft_close(int fd, char *str);


// executing
int         executing(t_data *data);
void        my_cd(t_env *list, char **com);
void        ft_echo(char **com, bool flag, int i);



// tools
void        exiterror(void);
bool        check_n_flag(char *str);
t_env       *env_new(t_env *lst, char *str);
t_env	    *env_last(t_env *lst);
char        **linked_list_to_array(t_env *list);
char        **sortexport(char **arr, int n);
void	    senv_clear(t_env **lst);
char        **linked_list_to_array(t_env *list);

t_env       *unset_env(t_env *list, char **com, t_data *data);
void        exit_myminishell(char **com, int flag);
char       	*join(char const *s1, char const *s2);
char        *get_my_path(t_env  *list, char **com, bool flag);
void        export(t_env *list, char **com);
void        printmyexport(t_env *list);
int         lenofmyenv(char **env);
void        exiterror(void);
t_env       *copieenv(char **env);
void        ft_putendle(char *str, int fd);
void        printmyenv(t_env *list);
t_env       *findmyindex(t_env *list, char *va);
void        change_mydir(t_env *list, char *path);
int         morethan2arg(char **com);
void        mypwd(t_env *env);
// void        ft_putendexp(char *str, int fd);


//  after the norm
void    set_env_after_export(t_env *list, char *key, char *value, char c, bool export_flag);
void    set_env_after_cd(t_env *list, char *key, char *value);
char    *findmyvar(t_env *list, t_env *head, char *va, bool flag);
void 	handlersignals();


// void        set_myenv(t_env *list, char *key, char *value, char c, bool export_flag);

#endif