# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: error01 <error01@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 14:29:42 by ksohail-          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/03/11 17:45:14 by error01          ###   ########.fr        #
=======
#    Updated: 2024/05/24 17:16:53 by ksohail-         ###   ########.fr        #
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
#                                                                              #
# **************************************************************************** #

SRC = ft_lstadd_back_bonus.c\
				ft_lstadd_front_bonus.c\
				ft_lstclear_bonus.c\
				ft_lstdelone_bonus.c\
				ft_lstiter_bonus.c\
				ft_lstlast_bonus.c\
				ft_lstmap_bonus.c\
				ft_lstnew_bonus.c\
				ft_lstsize_bonus.c\
				ft_atoi.c\
				ft_isascii.c\
				ft_memmove.c\
				ft_putstr_fd.c\
				ft_strjoin.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_strncmp.c\
				ft_tolower.c\
				ft_bzero.c\
				ft_isdigit.c\
				ft_memset.c\
				ft_split.c\
				ft_strlcat.c\
				ft_strnstr.c\
				ft_toupper.c\
				ft_calloc.c\
				ft_isprint.c\
				ft_memchr.c\
				ft_strchr.c\
				ft_strlcpy.c\
				ft_strrchr.c\
				ft_isalnum.c\
				ft_itoa.c\
				ft_memcmp.c\
				ft_strdup.c\
				ft_strlen.c\
				ft_strtrim.c\
				ft_isalpha.c\
				ft_memcpy.c\
				ft_striteri.c\
				ft_strmapi.c\
				ft_substr.c\
<<<<<<< HEAD
				get_next_line.c\
				get_next_line_utils.c\
				ft_printf.c\
				print_ch.c\
				print_i_d.c\
				print_p.c\
				print_str.c\
				print_u.c\
				print_x.c
=======
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = Libft.A
OBJ = $(SRC:.c=.o)


all: $(NAME)

<<<<<<< HEAD
$(NAME): run_script $(OBJ)
	@printf "\033[0;32m\nCompilation completed :-)\033[0m\n"
	@printf "\033[0;32mBuilding MyLib"
	@for i in 1 2 3; do \
        sleep 0.5; \
        printf "."; \
    done
	@printf "\n"
=======
$(NAME):	$(OBJ)
>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
	@ar rcs $(NAME) $(OBJ)

%.o:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@
<<<<<<< HEAD
	
run_script:
	@./script.sh
	
=======

>>>>>>> a7ef12afb3c0a0018eb894a6d98a9b954967380c
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all

.SECONDARY : ${OBJ}
.PHONY: all clean fclean re
