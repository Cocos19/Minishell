# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 09:47:54 by mprofett          #+#    #+#              #
#    Updated: 2023/04/17 14:27:44 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= minishell.c minishell_env.c minishell_execute.c minishell_free.c \
			minishell_input_validity.c minishell_heredoc.c \
			minishell_local_variables.c minishell_parser.c \
			minishell_parser_utils.c minishell_signals.c \
			minishell_utils.c minishell_temp.c minishell_terminal.c \
			minishell_tokens.c minishell_tokenize_special_characters.c \
			minishell_token_validity.c

SRC_BONUS	=

OBJ			= ${SRC:.c=.o}

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

LIBFT		= libft.a

LIBFT_PATH	= libft

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(C_FLAGS) -I/Users/mprofett/.brew/opt/readline/include -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	${CC} ${OBJ} -o  ${NAME} ${LIBFT} -I/Users/mprofett/.brew/opt/readline/include -L/Users/mprofett/.brew/opt/readline/lib -lreadline -fsanitize=address

${LIBFT}:
	${MAKE} bonus -C ${LIBFT_PATH}
	mv ${LIBFT_PATH}/${LIBFT} .

bonus: ${OBJ_BONUS} ${LIBFT}
	${CC} ${OBJ_BONUS} -o  ${NAME} ${LIBFT}

clean:
	${MAKE} clean -C ${LIBFT_PATH}
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME} ${LIBFT}

re:	fclean all

.PHONY:	all bonus clean fclean re
