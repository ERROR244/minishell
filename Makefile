NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -ggdb3 -g3 -lreadline -fsanitize=address  #-Werror #-v

SRCS = 	src/minishell.c Libft/ft_split.c Libft/ft_putstr_fd.c\
		src/lst.c Libft/ft_strjoin.c Libft/ft_strdup.c\
		Libft/ft_putchar_fd.c Libft/ft_strnstr.c Libft/ft_strncmp.c\
		Libft/ft_isalpha.c src/parsing.c src/parsing_utils3.c\
		src/parsing_utils1.c Libft/ft_strlen.c Libft/ft_lstsize_bonus.c\
		src/parsing_utils2.c src/errors0.c src/parsing_utils4.c\
		src/executing.c src/errors1.c src/parsing_utils5.c\
		Libft/ft_strcmp.c\


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
