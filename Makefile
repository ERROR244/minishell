NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./include

SRCS = 	Libft/ft_split.c\
		Libft/ft_putstr_fd.c\
		Libft/ft_strjoin.c\
		Libft/ft_strdup.c\
		Libft/ft_putchar_fd.c\
		Libft/ft_strnstr.c\
		Libft/ft_strncmp.c\
		Libft/ft_isalpha.c\
		Libft/ft_strlen.c\
		Libft/ft_lstsize_bonus.c\
		Libft/ft_strcmp.c\
		Libft/ft_isdigit.c\
		Libft/ft_isalnum.c\
		Libft/ft_strlcpy.c\
		Libft/ft_strchr.c\
		Libft/ft_itoa.c\
		Libft/ft_atoi.c\
		Libft/GC.c\
		src/minishell.c\
		src/parsing/expand_variable.c\
		src/parsing/open_heredoc.c\
		src/parsing/parsing_change_cmd_to_list.c\
		src/parsing/parsing_change_list_to_command_list.c\
		src/parsing/parsing_expand_vars.c\
		src/parsing/parsing_fill_in_commands_list.c\
		src/parsing/parsing_init_tokens.c\
		src/parsing/parsing_redirections_errors.c\
		src/parsing/parsing_split_with_redirections_pipe.c\
		src/parsing/parsing_split_with_words.c\
		src/parsing/parsing.c\
		src/parsing/update_command_list.c\
		src/lists/linked_list_handling_functions.c\
		src/signals/handlingsignals.c\
		src/executing/executing.c\
		src/executing/execute_command.c\
		src/executing/files_handeling.c\
		src/executing/wait_for_processes_and_print_errors_utils.c\
		src/errors_and_utils/env_and_expand_utils.c\
		src/errors_and_utils/errors_managment_and_heardoc.c\
		src/errors_and_utils/expand_utils.c\
		src/errors_and_utils/heredoc_and_lists_utils.c\
		src/errors_and_utils/lists_utils.c\
		src/errors_and_utils/some_printing_functions.c\
		src/errors_and_utils/wrapper_function.c\
		src/errors_and_utils/check_pipe_and_quotes_errors.c\
		src/builtins/cd.c\
		src/builtins/env.c\
		src/builtins/pwd.c\
		src/builtins/echo.c\
		src/builtins/export.c\
		src/builtins/unset_exit.c\

OBJ = $(SRCS:.c=.o)

AR  = ar rcs

RM = rm -rf 

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o minishell -lreadline


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
		@$(RM) $(OBJ)

fclean :
		@$(RM) $(OBJ) $(NAME)

re : fclean all

leak: all
	valgrind --leak-check=full \
	--show-leak-kinds=all --track-fds=all --trace-children=yes ./$(NAME)

.SECONDARY : ${OBJ}
