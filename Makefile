NAME = minishell

SRCS = main.c env.c cd.c pwd.c
SRCSLIBFT =  libft/ft_atoi.c libft/ft_itoa.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strlen.c  libft/ft_strncmp.c libft/ft_isdigit.c
OBJ = $(SRCS:.c=.o)
OBJLIBFT = $(SRCSLIBFT:.c=.o)

AR = ar rcs
CC = cc
CFLAGS = -l readline -ggdb3 -fsanitize=address
RM = rm -f
LIBFT = libft/libft.a
all: $(NAME)


$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(OBJLIBFT)
	make -C libft

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re