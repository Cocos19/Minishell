# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 14:04:13 by mprofett          #+#    #+#              #
#    Updated: 2023/06/21 13:46:03 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_strdup_tab.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_put_hexa_char_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c

SRCSB	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c \
		ft_printf_bonus.c ft_printf_getvalues_bonus.c \
		ft_printf_printvars_bonus.c ft_printf_putvalues_bonus.c \
		ft_free_str_array.c ft_strcmp.c \
		ft_expand.c ft_strjoin_and_free_srcs.c ft_substr_delimited.c \
		ft_is_empty_or_with_only_spaces.c ft_strarraylen.c \
		ft_strarrayjoin_and_free_srcs.c ft_skip_character.c \
		ft_add_to_str_array.c ft_strdup_array.c ft_print_str_array.c \
		ft_strndup.c ft_skip_all_but_character.c ft_sort_str_array.c \
		ft_print_str_array_fd.c ft_retrieve_from_str_array.c

OBJS	= ${SRCS:.c=.o}

OBJSB	= ${SRCSB:.c=.o}

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

all: ${NAME}

bonus: ${NAME} ${OBJSB}
	ar rc ${NAME} ${OBJSB}

clean:
	${RM} ${OBJSB} ${OBJS}

fclean: clean
	${RM} $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
