# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 14:29:42 by ksohail-          #+#    #+#              #
#    Updated: 2023/11/17 13:02:19 by ksohail-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_atoi.c\
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
		ft_substr.c

BONUS_SRCS =	ft_lstadd_back_bonus.c\
				ft_lstadd_front_bonus.c\
				ft_lstclear_bonus.c\
				ft_lstdelone_bonus.c\
				ft_lstiter_bonus.c\
				ft_lstlast_bonus.c\
				ft_lstmap_bonus.c\
				ft_lstnew_bonus.c\
				ft_lstsize_bonus.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(BONUS_OBJS) 

$(BONUS_OBJS):	$(BONUS_SRCS)
	$(CC) $(CFLAGS) -c $^
	ar rcs $(NAME) $(BONUS_OBJS)

%.o:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
