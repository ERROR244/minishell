NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -ggdb3 -g3 -fsanitize=address -fno-omit-frame-pointer#-w  #-v

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
		src/minishell.c\
		src/parsing.c\
		src/parsing_utils1.c\
		src/parsing_utils2.c\
		src/parsing_utils3.c\
		src/parsing_utils4.c\
		src/parsing_utils5.c\
		src/parsing_utils6.c\
		src/parsing_utils7.c\
		src/parsing_utils8.c\
		src/handlingsignals.c\
		src/utils0.c\
		src/utils1.c\
		src/utils2.c\
		src/utils3.c\
		src/utils4.c\
		src/utils5.c\
		src/utils6.c\
		src/utils7.c\
		src/utils8.c\
		src/utils9.c\
		src/cd.c\
		src/lst.c\
		src/tmp.c\
		src/env.c\
		src/pwd.c\
		src/echo.c\
		src/export.c\
		src/errors0.c\
		src/errors1.c\
		src/executing.c\
		src/unset_exit.c\
		src/open_heredoc.c\
		src/expand_variable.c

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

.SECONDARY : ${OBJ}
