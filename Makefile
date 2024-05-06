NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -ggdb3 -lreadline -g3 -fsanitize=address#-Werror -v

SRCS = 	src/minishell.c Libft/ft_split.c Libft/ft_putstr_fd.c\
		src/lst.c Libft/ft_strjoin.c Libft/ft_strdup.c\
		Libft/ft_putchar_fd.c Libft/ft_strnstr.c Libft/ft_strncmp.c\
		Libft/ft_isalpha.c src/parsing.c Libft/ft_split_msh.c\
		src/parsing_utils.c Libft/ft_strlen.c\
		src/errors.c\



OBJ = $(SRCS:.c=.o)

AR  = ar rcs

RM = rm -rf 

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o minishell 


%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

install:
	make
	cp ./minishell /user/local/bin/minishell

clean : 
		@$(RM) $(OBJ)

fclean :
		@$(RM) $(OBJ) $(NAME)

rminstall:
	rm -rf /user/local/bin/minishell

re : fclean all
