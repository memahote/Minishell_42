# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 17:45:41 by memahote          #+#    #+#              #
#    Updated: 2023/01/16 14:22:16 by memahote         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c \
					ft_split.c ft_strlcat.c ft_strncmp.c ft_substr.c \
					ft_atoi.c ft_isalpha.c ft_itoa.c ft_memcpy.c \
					ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c ft_strnstr.c \
					ft_tolower.c ft_bzero.c ft_isascii.c ft_memcpy.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c \
					ft_strrchr.c ft_toupper.c ft_calloc.c ft_isdigit.c \
					ft_memchr.c ft_memset.c ft_putstr_fd.c ft_strjoin.c \
					ft_strmapi.c ft_strtrim.c ft_striteri.c ft_strcomp.c \
					ft_printf.c ft_put_c.c ft_put_x.c ft_put_p.c ft_putd_i.c \
					ft_put_s.c ft_put_u.c ft_base.c ft_atol.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS			= $(SRCS:.c=.o)


HEADER			= libft.h
CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a

all:			$(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME):		$(OBJS) $(HEADER)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus

.SILENT:		all clean fclean re bonus %.o